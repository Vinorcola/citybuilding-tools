#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include "../file/ImageLoader.hpp"

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
        QTreeView* navigator;
        Viewer* viewer;

    public:
        MainWindow();
        virtual ~MainWindow();

    protected:
        void loadFile(const QString& filePath);
        void loadImage(const QModelIndex& index);
};

#endif // MAINWINDOW_HPP
