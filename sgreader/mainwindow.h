#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class Animation;
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
        Animation* animation;

        QAction* openAction;
        QAction* saveAction;
        QAction* extractAllAction;
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
        void startAnimation(int startingImageIndex, int endingImageIndex);
        void stopAnimation();

    private:
        void createChildren();
        void createMenu();
        void createActions();

        void loadFile(const QString &filename);
        void loadImage(const BitmapMetaData& bitmapMetaData, const ImageMetaData& imageMetaData);
        void clearImage();
};

#endif /* MAINWINDOW_H */
