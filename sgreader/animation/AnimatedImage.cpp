#include "AnimatedImage.hpp"



AnimatedImage::AnimatedImage() :
    QGraphicsPixmapItem(),
    images(),
    positions()
{

}



void AnimatedImage::registerImage(const QPixmap& pixmap, const QPoint& position)
{
    images.append(pixmap);
    positions.append(position);
}



void AnimatedImage::changeAnimationImage(int animationIndex)
{
    if (images.length() > 0) {
        setPixmap(images.at(animationIndex));
        setPos(positions.at(animationIndex));
    }
}
