#include "mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>

#include "animation/Animation.hpp"
#include "exception/FileException.hpp"
#include "file/BitmapMetaData.hpp"
#include "file/FileMetaData.hpp"
#include "file/ImageMetaData.hpp"
#include "file/ImageReader.hpp"
#include "gui/dialog/aboutdialog.h"
#include "gui/dialog/helpdialog.h"
#include "gui/dialog/licencedialog.h"
#include "gui/extractWizard/extractwizard.h"
#include "gui/AnimationController.hpp"
#include "gui/ImageDetails.hpp"
#include "gui/ImageDisplay.hpp"
#include "gui/ImageTree.hpp"
#include "gui/ImageTreeItem.hpp"

MainWindow::MainWindow() :
    QMainWindow(),
    imageReader(nullptr),
    appname("SGReader"),
    sgFile(nullptr),
    animation(nullptr)
{
	setWindowTitle(appname);
	setWindowIcon(QIcon(":/icon.png"));
	
	createChildren();
	createActions();
	createMenu();
	
	if (QCoreApplication::arguments().size() > 1) {
		loadFile(QCoreApplication::arguments().at(1));
	}
	
    resize(1200, 600);
}

MainWindow::~MainWindow()
{
    if (animation != nullptr) {
        delete animation;
    }
    if (sgFile != nullptr) {
        delete sgFile;
    }
    if (imageReader != nullptr) {
        delete imageReader;
    }
}

/* Slots */
void MainWindow::openFile() {
	QString newfilename = QFileDialog::getOpenFileName(this, "Load SG file",
		filename, "Sierra Graphics files (*.sg2 *.sg3)");
	if (!newfilename.isEmpty()) {
		loadFile(newfilename);
	}
}

void MainWindow::saveFile() {
	QString suggestion = filename.replace(filename.length() - 4, 4, ".png");
	QString pngfilename = QFileDialog::getSaveFileName(this, tr("Save Image"),
		filename, "PNG File (*.png)");
	if (!pngfilename.isEmpty()) {
		Q_ASSERT(!image.isNull());
		if (!pngfilename.endsWith(".png", Qt::CaseInsensitive)) {
			// Don't care if the filename exists already, just overwrite:
			// user should be smart enough to add .png itself
			pngfilename += ".png";
		}
		if (image.save(pngfilename, "png")) {
			qDebug("Image saved");
		} else {
			qDebug("Image could NOT be saved");
		}
	}
}

void MainWindow::extractAll() {
	ExtractWizard wizard(this);
	wizard.exec();
}

void MainWindow::licence() {
	LicenceDialog dialog(this, appname);
	dialog.exec();
}

void MainWindow::help() {
	HelpDialog dialog(this, appname);
	dialog.exec();
}

void MainWindow::about() {
	AboutDialog dialog(this, appname, QString("1.1 (2019-01-12)"),
		tr("Copyright (C) 2007-2020 Bianca van Schaik &lt;pecuniam@gmail.com&gt;"),
		tr("Read graphics files (*.sg2 and *.sg3) from Impressions citybuilding games.\n\n"
		"This program is distributed in the hope that it will be useful,\n"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
		"See the GNU General Public License or Help->Licence for more details.\n"));
    dialog.exec();
}

void MainWindow::startAnimation(int startingImageIndex, int endingImageIndex)
{
    // TODO
}

void MainWindow::stopAnimation()
{
    if (animation == nullptr) {
        return;
    }

    animation->stop();
    delete animation;
    animation = nullptr;
}

void MainWindow::treeSelectionChanged()
{
    QList<QTreeWidgetItem*> items = treeWidget->selectedItems();
    if (items.size() != 1) {
        qDebug("No selection");
        clearImage();
        return;
    }

    auto imageItem(dynamic_cast<ImageTreeItem*>(items.at(0)));
    if (imageItem) {
        loadImage(imageItem->getBitmapMetaData(), imageItem->getImageMetaData());
    }
    else {
        clearImage();
    }
}

void MainWindow::loadFile(const QString &filename)
{
    treeWidget->clear();
    treeWidget->setHeaderLabel("No file loaded");
    clearImage();

    if (sgFile != nullptr) {
        delete sgFile;
    }
    sgFile = new FileMetaData(filename);

    this->filename = sgFile->getFileInfo().fileName();
    setWindowTitle(QString("%0 - %1").arg(this->filename).arg(appname));
    treeWidget->setHeaderLabel(this->filename);

    const int bitmapQuantity(sgFile->getBitmapQuantity());
    if (bitmapQuantity == 1) {
        // Just have a long list of images
        auto& bitmapMetaData(sgFile->getBitmapMetaData(0));
        const int imageQuantity(sgFile->getTotalImageQuantity());
        for (int imageIndex(0); imageIndex < imageQuantity; ++imageIndex) {
            new ImageTreeItem(treeWidget, bitmapMetaData, imageIndex, sgFile->getImageMetaData(imageIndex));
        }
    }
    else {
        // Split up by file
        for (int bitmapIndex(0); bitmapIndex < bitmapQuantity; ++bitmapIndex) {
            auto& bitmapMetaData(sgFile->getBitmapMetaData(bitmapIndex));
            auto bitmapItem(new QTreeWidgetItem(
                treeWidget,
                QStringList(bitmapMetaData.getTitle())
            ));

            const int imageQuantity(bitmapMetaData.getRegisteredImageQuantity());
            for (int imageIndex(0); imageIndex < imageQuantity; imageIndex++) {
                new ImageTreeItem(bitmapItem, bitmapMetaData, imageIndex, bitmapMetaData.getImageMetaData(imageIndex));
            }
        }
    }

    treeWidget->scrollToTop();
    if (imageReader != nullptr) {
        delete imageReader;
    }
    imageReader = new ImageReader();
}

void MainWindow::loadImage(const BitmapMetaData& bitmapMetaData, const ImageMetaData& imageMetaData)
{
    try {
        auto imageFile(imageReader->readImage(*sgFile, bitmapMetaData, imageMetaData));

        imageDisplay->changeImage(QPixmap::fromImage(imageFile), imageMetaData.getPositionOffset());
        imageDetails->changeImageDetails(imageMetaData.getBinaryDescription());
        saveAction->setEnabled(true);
    }
    catch (FileException exception) {
        imageDisplay->clear();
        imageDetails->setError("Could not load image:\n" + exception.getMessage());
        saveAction->setEnabled(false);
    }
}

void MainWindow::clearImage()
{
    imageDisplay->clear();
    imageDetails->clear();
    saveAction->setEnabled(false);
}

/* Creating stuff */
void MainWindow::createChildren()
{
    auto leftDock(new QDockWidget("Image browser", this));
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    treeWidget = new ImageTree(leftDock);
    treeWidget->setHeaderLabel("No file loaded");
    treeWidget->setUniformRowHeights(true);
    leftDock->setWidget(treeWidget);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    auto rightDock(new QDockWidget("Image details", this));
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    imageDetails = new ImageDetails(rightDock);
    rightDock->setWidget(imageDetails);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    imageDisplay = new ImageDisplay(this);

    auto animationController(new AnimationController(this));
    connect(animationController, &AnimationController::requiredAnimationStart, this, &MainWindow::startAnimation);
    connect(animationController, &AnimationController::requiredAnimationEnd, this, &MainWindow::stopAnimation);

    auto mainWidget(new QWidget());
    auto layout(new QVBoxLayout());
    layout->addWidget(imageDisplay);
    layout->addWidget(animationController);
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    connect(treeWidget, &QTreeWidget::itemSelectionChanged, this, &MainWindow::treeSelectionChanged);
}

void MainWindow::createActions() {
	openAction = new QAction("&Open...", this);
	openAction->setShortcut(tr("Ctrl+O"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
	
	saveAction = new QAction("&Save image...", this);
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAction->setEnabled(false);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
	
	extractAllAction = new QAction("&Batch extract...", this);
	connect(extractAllAction, SIGNAL(triggered()), this, SLOT(extractAll()));
	
	exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	
	helpAction = new QAction(tr("&Help"), this);
	helpAction->setShortcut(tr("F1"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
	
	licenceAction = new QAction(tr("&Licence"), this);
	connect(licenceAction, SIGNAL(triggered()), this, SLOT(licence()));
	
	aboutAction = new QAction(tr("&About %0").arg(appname), this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenu() {
	QMenu *menu;
	
	menu = menuBar()->addMenu("&File");
	menu->addAction(openAction);
	menu->addAction(saveAction);
	menu->addSeparator();
	menu->addAction(extractAllAction);
	menu->addSeparator();
	menu->addAction(exitAction);
	
	menu = menuBar()->addMenu("&Help");
	menu->addAction(helpAction);
	menu->addSeparator();
	menu->addAction(licenceAction);
	menu->addAction(aboutAction);
}
