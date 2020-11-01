#include "MainWindow.hpp"

#include <QtCore/QStandardPaths>
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
#include "../file/animation/CharacterAnimationModel.hpp"
#include "../file/FileMetaData.hpp"
#include "../file/FileModel.hpp"
#include "../file/ImageMetaData.hpp"
#include "AnimationController.hpp"
#include "ControlPanel.hpp"
#include "InfoDialog.hpp"



MainWindow::MainWindow() :
    QMainWindow(),
    imageLoader(),
    currentFileMetaData(nullptr),
    currentFileModel(nullptr),
    animationModel(nullptr),
    browser(new QTreeView(this)),
    detailsDisplay(new BinaryDetails(this)),
    viewer(new Viewer(this)),
    animationAction(new QAction(QIcon(":/icon/animation"), tr("&Animation"), this)),
    animationPlayAction(new AnimationController(this, browser))
{
    // Configure window.
    setWindowTitle("SG Reader");
    setWindowIcon(QIcon(":/icon/main"));
    setMinimumSize(1000, 600);
    setCentralWidget(viewer);

    // Configure actions.
    auto quitAction(new QAction(QIcon(":/icon/quit"), tr("&Quit"), this));
    quitAction->setShortcut(tr("Ctrl+Q", "Quit action shortcut"));
    connect(quitAction, &QAction::triggered, this, &QMainWindow::close);

    auto openFileAction(new QAction(QIcon(":/icon/open-file"), tr("&Open"), this));
    openFileAction->setShortcut(tr("Ctrl+O", "Open file action shortcut"));
    connect(openFileAction, &QAction::triggered, [this]() {
        QString currentDirectory(
            currentFileMetaData == nullptr ?
                QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first() :
                currentFileMetaData->getFileInfo().absoluteFilePath()
        );
        auto file(QFileDialog::getOpenFileName(this, "Load SG file", currentDirectory, "Sierra Graphics files (*.sg2 *.sg3)"));
        if (!file.isEmpty()) {
            loadFile(file);
        }
    });

    auto infoAction(new QAction(QIcon(":/icon/info"), tr("&Info"), this));
    infoAction->setShortcut(QKeySequence::HelpContents);
    connect(infoAction, &QAction::triggered, [this]() {
        InfoDialog dialog(this);
        dialog.exec();
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

    connect(animationPlayAction, &AnimationController::updateAnimation, [this](const QModelIndex& animationIndex) {
        if (animationModel == nullptr) {
            return;
        }

        browser->selectionModel()->setCurrentIndex(animationIndex, QItemSelectionModel::SelectCurrent);
    });

    // Configure toolbar.
    auto toolBar(addToolBar("File"));
    toolBar->setMovable(false);
    toolBar->setIconSize({32, 32});
    toolBar->addAction(quitAction);
    toolBar->addSeparator();
    toolBar->addAction(openFileAction);
    toolBar->addAction(animationAction);
    toolBar->addAction(animationPlayAction);
    auto spacer(new QWidget());
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);
    toolBar->addAction(infoAction);

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
    imageLoader.clearCache();
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



void MainWindow::loadImage(const QModelIndex& index, const QModelIndex& animationIndex)
{
    if (currentFileModel == nullptr) {
        return;
    }

    if (animationModel != nullptr && animationModel->hasBackgroundImage(animationIndex)) {
        viewer->changeImage(
            currentFileModel->getPixmap(animationModel->getMainModelRootImageIndex()),
            currentFileModel->getPosition(animationModel->getMainModelRootImageIndex()),
            currentFileModel->getPixmap(index),
            currentFileModel->getRawPositionOffset(animationModel->getMainModelRootImageIndex()),
            currentFileModel->displayTile(index)
        );
    }
    else {
        viewer->changeImage(
            currentFileModel->getPixmap(index),
            currentFileModel->getPosition(index),
            currentFileModel->displayTile(index)
        );
    }
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
        animationPlayAction->start(*animationModel);
    }
    else if (imageMetaData->isCharacter()) {
        animationModel = new CharacterAnimationModel(this, *currentFileModel, currentIndex);
        updateBrowser(QModelIndex());
        animationPlayAction->start(*animationModel);
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
    animationPlayAction->reset();
}



void MainWindow::updateBrowser(const QModelIndex& selection)
{
    if (animationModel == nullptr) {
        browser->setModel(currentFileModel);
        connect(browser->selectionModel(), &QItemSelectionModel::selectionChanged, [this](const QItemSelection& selected) {
            auto selectedIndexes(selected.indexes());
            if (selectedIndexes.length() == 1) {
                loadImage(selectedIndexes.first(), QModelIndex());
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
                loadImage(animationModel->getMainModelImageIndex(selectedIndexes.first()), selectedIndexes.first());
            }
            animationPlayAction->updateCurrentIndex(selectedIndexes.first());
        });
    }
}
