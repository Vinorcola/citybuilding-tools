#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include "../file/ImageLoader.hpp"

class AbstractAnimationModel;
class BinaryDetails;
class FileMetaData;
class FileModel;
class QTreeView;
class Viewer;

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        QAction* animationAction;
        ImageLoader imageLoader;
        FileMetaData* currentFileMetaData;
        FileModel* currentFileModel;
        AbstractAnimationModel* animationModel;
        QTreeView* browser;
        BinaryDetails* detailsDisplay;
        Viewer* viewer;

    public:
        MainWindow();
        virtual ~MainWindow();

    protected:
        void loadFile(const QString& filePath);
        void clearFile();
        void loadImage(const QModelIndex& index);
};

#endif // MAINWINDOW_HPP
