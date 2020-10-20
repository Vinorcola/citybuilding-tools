#include "ImageDisplay.hpp"

#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>



ImageDisplay::ImageDisplay(QWidget* parent) :
    QGraphicsView(parent),
    imageItem(new QGraphicsPixmapItem())
{
    QPainter painter;

    // Generate background image.
    QImage background(16, 16, QImage::Format_RGB32);
    background.fill(Qt::white);
    painter.begin(&background);
    QColor grey(213, 213, 213);
    painter.setBrush({ grey, Qt::SolidPattern });
    painter.setPen(Qt::NoPen);
    painter.drawRect(QRect(8, 0, 8, 8));
    painter.drawRect(QRect(0, 8, 8, 8));
    painter.end();

    // Generate tile image.
    QImage tile(58, 30, QImage::Format_ARGB32);
    tile.fill(Qt::transparent);
    painter.begin(&tile);
    painter.setPen(Qt::darkGreen);
    for (int y(0); y < 15; ++y) {
        int xBegin((58 / 2) - (2 * y) - 1);
        int xEnd((58 / 2) + (2 * y));
        painter.drawLine(xBegin, y, xEnd, y);
        painter.drawLine(xBegin, 29 - y, xEnd, 29 - y);
    }
    painter.end();
    auto tileItem(new QGraphicsPixmapItem());
    tileItem->setPixmap(QPixmap::fromImage(tile));
    tileItem->setPos(-29, -15);

    auto scene(new QGraphicsScene(this));
    scene->setBackgroundBrush(background);
    scene->addItem(tileItem);
    scene->addItem(imageItem);
    setScene(scene);
    scale(2.0, 2.0);
}



void ImageDisplay::changeImage(const QPixmap& image, const QPoint offset)
{
    imageItem->setPixmap(image);
    imageItem->setPos(offset.x(), offset.y());
}



void ImageDisplay::clear()
{
    this->imageItem->setPixmap(QPixmap());
}
