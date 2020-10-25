#ifndef ANIMATEDIMAGE_HPP
#define ANIMATEDIMAGE_HPP

#include <QtWidgets/QGraphicsPixmapItem>

class AnimatedImage : public QGraphicsPixmapItem
{
    private:
        QList<QPixmap> images;
        QList<QPoint> positions;

    public:
        AnimatedImage();

        void registerImage(const QPixmap& pixmap, const QPoint& position);
        void changeAnimationImage(int animationIndex);
};

#endif // ANIMATEDIMAGE_HPP
