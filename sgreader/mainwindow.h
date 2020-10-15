#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "sgfile.h"
#include "sgimage.h"

class ImageDetails;
class ImageDisplay;
class ImageTree;
class QAction;
class QTreeWidget;

class MainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
		MainWindow();
		//~MainWindow();
		
	
	private slots:
		void openFile();
		void saveFile();
		void extractAll();
		void treeSelectionChanged();
		void help();
		void licence();
		void about();
		
	private:
		void createChildren();
		void createMenu();
		void createActions();
		
		void loadFile(const QString &filename);
		void loadImage(SgImage *image);
		void clearImage();
		
        ImageTree *treeWidget;
        ImageDetails *imageDetails;
        ImageDisplay* imageDisplay;
		QString filename;
		QString appname;
		QImage image;
		SgFile *sgFile;
		
		QAction *openAction;
		QAction *saveAction;
		QAction *extractAllAction;
		QAction *exitAction;
		
		QAction *helpAction;
		QAction *licenceAction;
		QAction *aboutAction;
};

#endif /* MAINWINDOW_H */
