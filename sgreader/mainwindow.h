#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class BitmapMetaData;
class FileMetaData;
class ImageDetails;
class ImageDisplay;
class ImageMetaData;
class ImageReader;
class ImageTree;
class QAction;
class QTreeWidget;

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        ImageReader* imageReader;
        ImageTree* treeWidget;
        ImageDetails* imageDetails;
        ImageDisplay* imageDisplay;
        QString filename;
        QString appname;
        QImage image;
        FileMetaData* sgFile;

        QAction* openAction;
        QAction* saveAction;
        QAction* extractAllAction;
        QAction* animationAction;
        QAction* exitAction;

        QAction* helpAction;
        QAction* licenceAction;
        QAction* aboutAction;

    public:
        MainWindow();
        virtual ~MainWindow();

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
        void loadImage(const ImageMetaData& imageMetaData);
        void clearImage();
};

#endif /* MAINWINDOW_H */
