#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets/QGraphicsView>

class ImageGraphics;
class ImageLoader;
class ImageMetaData;
class ImageScene;

class Viewer : public QGraphicsView
{
        Q_OBJECT

    private:
        ImageScene* scene;
        ImageGraphics* image;

    public:
        Viewer(QWidget* parent, ImageLoader& imageLoader);

        void changeImage(const ImageMetaData& imageMetaData);
        void clear();

    public slots:
        void changeZoom(qreal zoom);
};

#endif // VIEWER_HPP
