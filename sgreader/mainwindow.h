#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class BitmapMetaData;
class ControlPanel;
class FileMetaData;
class BinaryDetails;
class ImageLoader;
class ImageMetaData;
class ImageTree;
class QAction;
class QTreeWidget;
class Viewer;

class LegacyMainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        ImageLoader* imageLoader;
        ImageTree* treeWidget;
        BinaryDetails* imageDetails;
        ControlPanel* controlPanel;
        Viewer* imageViewer;
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
        LegacyMainWindow();
        virtual ~LegacyMainWindow();

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
