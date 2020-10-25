#include "AnimatedImageGraphics.hpp"



AnimatedImageGraphics::AnimatedImageGraphics(QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    images(),
    positions()
{

}



void AnimatedImageGraphics::registerImage(const QPixmap& pixmap, const QPoint& position)
{
    images.append(pixmap);
    positions.append(position);
}



void AnimatedImageGraphics::changeAnimationImage(int animationIndex)
{
    if (images.length() > 0) {
        setPixmap(images.at(animationIndex));
        setPos(positions.at(animationIndex));
    }
}
