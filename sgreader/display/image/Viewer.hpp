#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets/QGraphicsView>

class ImageGraphics;
class ImageScene;

class Viewer : public QGraphicsView
{
        Q_OBJECT

    private:
        ImageScene* scene;
        ImageGraphics* image;

    public:
        explicit Viewer(QWidget* parent);

        void changeImage(const QPixmap& pixmap, const QPoint& position, bool displayTile);
        void changeImage(
            const QPixmap& backgroundPixmap,
            const QPoint& backgroundPosition,
            const QPixmap& pixmap,
            const QPoint& position,
            bool displayTile
        );
        void clear();

    public slots:
        void changeZoom(qreal zoom);
};

#endif // VIEWER_HPP
