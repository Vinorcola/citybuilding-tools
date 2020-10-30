#ifndef IMAGEGRAPHICS_HPP
#define IMAGEGRAPHICS_HPP

#include <QtWidgets/QGraphicsItem>

class AnimatedImageGraphics;

/**
 * @brief Display an image (or a set of animated images).
 */
class ImageGraphics : public QGraphicsItem
{
    private:
        QGraphicsPixmapItem* tileImage;
        QGraphicsPixmapItem* mainImage;
        AnimatedImageGraphics* animation;

    public:
        ImageGraphics();

        void displayImage(const QPixmap& image, const QPoint& position, bool displayTile);
        void displayImageWithAnimation();

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // IMAGEGRAPHICS_HPP
