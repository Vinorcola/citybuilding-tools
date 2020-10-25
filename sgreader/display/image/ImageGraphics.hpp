#ifndef IMAGEGRAPHICS_HPP
#define IMAGEGRAPHICS_HPP

#include <QtWidgets/QGraphicsItem>

class AnimatedImageGraphics;
class ImageLoader;
class ImageMetaData;

/**
 * @brief Display an image (or a set of animated images).
 */
class ImageGraphics : public QGraphicsItem
{
    private:
        ImageLoader& imageLoader;
        QGraphicsPixmapItem* tileImage;
        QGraphicsPixmapItem* mainImage;
        AnimatedImageGraphics* animation;

    public:
        explicit ImageGraphics(ImageLoader& imageLoader);

        void displayImage(const ImageMetaData& imageMetaData);
        void displayImageWithAnimation(const ImageMetaData& imageMetaData);

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // IMAGEGRAPHICS_HPP
