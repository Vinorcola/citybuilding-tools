#include "ImageGraphics.hpp"

#include <QtGui/QPainter>

#include "AnimatedImageGraphics.hpp"

// TODO: Review to handle Emperor size.
const int TILE_WIDTH(58);
const int TILE_HALF_WIDTH(TILE_WIDTH / 2);
const int TILE_HEIGHT((TILE_WIDTH + 2) / 2);
const int TILE_HALF_HEIGHT(TILE_HEIGHT / 2);



ImageGraphics::ImageGraphics() :
    QGraphicsItem(),
    tileImage(new QGraphicsPixmapItem(this)),
    mainImage(new QGraphicsPixmapItem(this)),
    animation(new AnimatedImageGraphics(this))
{
    // Generate tile image.
    QImage tile(TILE_WIDTH, TILE_HEIGHT, QImage::Format_ARGB32);
    tile.fill(Qt::transparent);
    QPainter painter(&tile);
    painter.setPen(Qt::green);
    for (int y(0); y < TILE_HALF_HEIGHT; ++y) {
        int xBegin(TILE_HALF_WIDTH - (2 * y) - 1);
        int xEnd(TILE_HALF_WIDTH + (2 * y));
        painter.drawLine(xBegin, y, xEnd, y);
        painter.drawLine(xBegin, TILE_HEIGHT - 1 - y, xEnd, TILE_HEIGHT - 1 - y);
    }
    painter.end();

    tileImage->setPixmap(QPixmap::fromImage(tile));
    tileImage->setPos(-TILE_HALF_WIDTH, -TILE_HEIGHT);
    tileImage->setVisible(false);
}



void ImageGraphics::displayImage(const QPixmap& image, const QPoint& position, bool displayTile)
{
    mainImage->setPixmap(image);
    mainImage->setPos(position);
    tileImage->setVisible(displayTile);
    animation->setVisible(false);
}



void ImageGraphics::displayImageWithAnimation()
{
    // TODO
}



QRectF ImageGraphics::boundingRect() const
{
    return {};
}



void ImageGraphics::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{

}
