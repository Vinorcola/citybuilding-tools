#ifndef IMAGEDISPLAY_HPP
#define IMAGEDISPLAY_HPP

#include <QtWidgets/QGraphicsView>

class QGraphicsPixmapItem;
class QPixmap;

class ImageDisplay : public QGraphicsView
{
        Q_OBJECT

    private:
        QGraphicsPixmapItem* imageItem;

    public:
        ImageDisplay(QWidget* parent = nullptr);

        void changeImage(const QPixmap& image, const QPoint offset);

        void clear();
};

#endif // IMAGEDISPLAY_HPP
