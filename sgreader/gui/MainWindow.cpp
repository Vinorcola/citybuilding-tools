#include "MainWindow.hpp"

#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>

#include "../display/binary/BinaryDetails.hpp"
#include "../display/image/Viewer.hpp"
#include "../exception/FileException.hpp"
#include "../file/animation/AbstractAnimationModel.hpp"
#include "../file/animation/BuildingAnimationModel.hpp"
#include "../file/FileMetaData.hpp"
#include "../file/FileModel.hpp"
#include "../file/ImageMetaData.hpp"
#include "ControlPanel.hpp"



MainWindow::MainWindow() :
    QMainWindow(),
    animationAction(new QAction(QIcon(":/animation-icon"), tr("&Animation"), this)),
    imageLoader(),
    currentFileMetaData(nullptr),
    currentFileModel(nullptr),
    animationModel(nullptr),
    browser(new QTreeView(this)),
    detailsDisplay(new BinaryDetails(this)),
    viewer(new Viewer(this))
{
    // Configure window.
    setWindowTitle("SG Reader");
    setWindowIcon(QIcon(":/icon.png"));
    setMinimumSize(1000, 600);
    setCentralWidget(viewer);

    // Configure actions.
    auto quitAction(new QAction(QIcon(":/quit-icon"), tr("&Quit"), this));
    quitAction->setShortcut(tr("Ctrl+Q", "Quit action shortcut"));
    connect(quitAction, &QAction::triggered, this, &QMainWindow::close);

    auto openFileAction(new QAction(QIcon(":/open-file-icon"), tr("&Open"), this));
    openFileAction->setShortcut(tr("Ctrl+O", "Open file action shortcut"));
    connect(openFileAction, &QAction::triggered, [this]() {
        auto file(QFileDialog::getOpenFileName(this, "Load SG file", {}, "Sierra Graphics files (*.sg2 *.sg3)"));
        if (!file.isEmpty()) {
            loadFile(file);
        }
    });

    animationAction->setShortcut(tr("Ctrl+A", "Animation action shortcut"));
    animationAction->setCheckable(true);
    animationAction->setEnabled(false);
    connect(animationAction, &QAction::triggered, [this](bool checked) {
        if (checked) {
            startAnimation();
        }
        else {
            stopAnimation();
        }
    });

    // Configure toolbar.
    auto toolBar(addToolBar("File"));
    toolBar->setMovable(false);
    toolBar->setIconSize({32, 32});
    toolBar->addAction(quitAction);
    toolBar->addSeparator();
    toolBar->addAction(openFileAction);
    toolBar->addAction(animationAction);

    // Configure docks.
    browser->setHeaderHidden(true);

    auto leftDock(new QDockWidget("Image browser", this));
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    leftDock->setWidget(browser);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    auto rightDock(new QDockWidget("Details", this));
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    rightDock->setWidget(detailsDisplay);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    // Confiure status bar.
    auto controlPanel(new ControlPanel(this));
    connect(controlPanel, &ControlPanel::zoomChanged, viewer, &Viewer::changeZoom);

    auto statusBar(new QStatusBar(this));
    statusBar->addWidget(controlPanel);
    setStatusBar(statusBar);
}



MainWindow::~MainWindow()
{
    if (currentFileMetaData!= nullptr) {
        delete currentFileMetaData;
    }
}



void MainWindow::loadFile(const QString& filePath)
{
    clearFile();

    try {
        currentFileMetaData = new FileMetaData(filePath);
        currentFileModel = new FileModel(this, imageLoader, *currentFileMetaData);
        updateBrowser(QModelIndex());
    }
    catch (FileException exception) {
        detailsDisplay->setError(exception.getMessage());
    }
}



void MainWindow::clearFile()
{
    if (currentFileMetaData!= nullptr) {
        delete currentFileMetaData;
        currentFileMetaData = nullptr;
    }
    if (currentFileModel != nullptr) {
        delete currentFileModel;
        currentFileModel = nullptr;
    }
    detailsDisplay->clear();
    animationAction->setEnabled(false);
}



void MainWindow::loadImage(const QModelIndex& index)
{
    if (currentFileModel == nullptr) {
        return;
    }

    viewer->changeImage(
        currentFileModel->getPixmap(index),
        currentFileModel->getPosition(index),
        currentFileModel->displayTile(index)
    );
    detailsDisplay->changeBinaryDetails(currentFileModel->getBinaryDetails(index));
    animationAction->setEnabled(animationModel != nullptr || currentFileModel->canBeAnimated(index));
}



void MainWindow::startAnimation()
{
    if (animationModel != nullptr) {
        delete animationModel;
    }
    auto currentIndex(browser->selectionModel()->currentIndex());
    auto imageMetaData(currentFileModel->getImageMetaData(currentIndex));
    if (imageMetaData == nullptr) {
        return;
    }

    if (imageMetaData->isBuilding()) {
        animationModel = new BuildingAnimationModel(this, *currentFileModel, currentIndex);
        updateBrowser(QModelIndex());
    }
    else {
        detailsDisplay->setError("Unknown animation type.");
    }
}



void MainWindow::stopAnimation()
{
    if (animationModel == nullptr) {
        return;
    }
    auto initialImageIndex(animationModel->getMainModelRootImageIndex());

    delete animationModel;
    animationModel = nullptr;

    updateBrowser(initialImageIndex);
}



void MainWindow::updateBrowser(const QModelIndex& selection)
{
    if (animationModel == nullptr) {
        browser->setModel(currentFileModel);
        connect(browser->selectionModel(), &QItemSelectionModel::selectionChanged, [this](const QItemSelection& selected) {
            auto selectedIndexes(selected.indexes());
            if (selectedIndexes.length() == 1) {
                loadImage(selectedIndexes.first());
            }
        });
        if (selection.isValid()) {
            browser->selectionModel()->setCurrentIndex(selection, QItemSelectionModel::SelectCurrent);
        }
    }
    else {
        browser->setModel(animationModel);
        connect(browser->selectionModel(), &QItemSelectionModel::selectionChanged, [this](const QItemSelection& selected) {
            auto selectedIndexes(selected.indexes());
            if (selectedIndexes.length() == 1) {
                loadImage(animationModel->getMainModelImageIndex(selectedIndexes.first()));
            }
        });
        browser->selectionModel()->setCurrentIndex(
            animationModel->index(0, 0, animationModel->index(0, 0)),
            QItemSelectionModel::SelectCurrent
        );
    }
}
