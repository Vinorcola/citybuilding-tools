#ifndef ANIMATEDIMAGEGRAPHICS_HPP
#define ANIMATEDIMAGEGRAPHICS_HPP

#include <QtWidgets/QGraphicsPixmapItem>

/**
 * @brief Handle the graphics of an animated image.
 */
class AnimatedImageGraphics : public QGraphicsPixmapItem
{
    private:
        QList<QPixmap> images;
        QList<QPoint> positions;

    public:
        AnimatedImageGraphics(QGraphicsItem* parent);

        void registerImage(const QPixmap& pixmap, const QPoint& position);
        void changeAnimationImage(int animationIndex);
};

#endif // ANIMATEDIMAGEGRAPHICS_HPP
