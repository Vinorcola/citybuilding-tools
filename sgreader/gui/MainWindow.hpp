#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include "../file/ImageExporter.hpp"
#include "../file/ImageLoader.hpp"

class AbstractAnimationModel;
class AnimationController;
class BinaryDetails;
class FileMetaData;
class FileModel;
class QTreeView;
class Viewer;

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        ImageLoader imageLoader;
        ImageExporter imageExporter;
        FileMetaData* currentFileMetaData;
        FileModel* currentFileModel;
        AbstractAnimationModel* animationModel;
        QTreeView* browser;
        BinaryDetails* detailsDisplay;
        Viewer* viewer;
        QAction* animationAction;
        AnimationController* animationPlayAction;

    public:
        MainWindow();
        virtual ~MainWindow();

    protected:
        void loadFile(const QString& filePath);
        void clearFile();
        void loadImage(const QModelIndex& index, const QModelIndex& animationIndex);
        void startAnimation();
        void stopAnimation();
        void updateBrowser(const QModelIndex& selection);

    protected slots:
        void saveImage();
};

#endif // MAINWINDOW_HPP
