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

#include "gui/extractWizard/extractwizard.h"
#include "gui/ImageDetails.hpp"
#include "gui/ImageDisplay.hpp"
#include "gui/ImageTree.hpp"
#include "aboutdialog.h"
#include "helpdialog.h"
#include "imagetreeitem.h"
#include "licencedialog.h"

MainWindow::MainWindow()
	: QMainWindow(), appname("SGReader")
{
	setWindowTitle(appname);
	setWindowIcon(QIcon(":/icon.png"));
	
	createChildren();
	createActions();
	createMenu();
	
	if (QCoreApplication::arguments().size() > 1) {
		loadFile(QCoreApplication::arguments().at(1));
	}
	
    resize(1000, 600);
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

void MainWindow::treeSelectionChanged() {
	
	QList<QTreeWidgetItem*> items = treeWidget->selectedItems();
	if (items.size() != 1) {
		qDebug("No selection");
		clearImage();
		return;
	}
	
	QTreeWidgetItem *item = items.at(0);
	
	if (item->type() == ImageTreeItem::ItemType) {
		ImageTreeItem *imageitem = (ImageTreeItem *)item;
		loadImage(imageitem->image());
	} else {
		clearImage();
	}
}

void MainWindow::loadFile(const QString &filename) {
	treeWidget->clear();
	treeWidget->setHeaderLabel("No file loaded");
	clearImage();
	
	sgFile = new SgFile(filename);
	if (!sgFile->load()) {
		setWindowTitle(appname);
		return;
	}
	
	QFileInfo fi(filename);
	
	this->filename = filename;
	setWindowTitle(QString("%0 - %1").arg(fi.fileName()).arg(appname));
	
	treeWidget->setHeaderLabel(fi.fileName());
	
	if (sgFile->bitmapCount() == 1 ||
			sgFile->imageCount(0) == sgFile->totalImageCount()) {
		// Just have a long list of images
		int numImages = sgFile->totalImageCount();
		for (int i = 0; i < numImages; i++) {
			new ImageTreeItem(treeWidget, i, sgFile->image(i));
		}
	} else {
		// Split up by file
		int numBitmaps = sgFile->bitmapCount();
		for (int b = 0; b < numBitmaps; b++) {
			QTreeWidgetItem *bitmapItem =
				new QTreeWidgetItem(treeWidget,
					QStringList(sgFile->getBitmapDescription(b)));
			
			int numImages = sgFile->imageCount(b);
			for (int i = 0; i < numImages; i++) {
				new ImageTreeItem(bitmapItem, i, sgFile->image(b, i));
			}
		}
	}
	treeWidget->scrollToTop();
}

void MainWindow::loadImage(SgImage *img)
{
    bool imageLoaded(imageDisplay->changeImage(*img));
    if (imageLoaded) {
        imageDetails->changeImage(*img);
    }
    else {
        imageDetails->clear();
    }
    saveAction->setEnabled(imageLoaded);
}

void MainWindow::clearImage() {
    imageDisplay->clear();
    imageDetails->clear();
    saveAction->setEnabled(false);
}

/* Creating stuff */
void MainWindow::createChildren()
{
    treeWidget = new ImageTree(this);
    treeWidget->setHeaderLabel("No file loaded");
    treeWidget->setUniformRowHeights(true);

    auto leftDock(new QDockWidget("Image browser", this));
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    leftDock->setWidget(treeWidget);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    imageDetails = new ImageDetails(this);
    auto rightDock(new QDockWidget("Image details", this));
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    rightDock->setWidget(imageDetails);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    imageDisplay = new ImageDisplay(this);
    setCentralWidget(imageDisplay);

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
