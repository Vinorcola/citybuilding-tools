#include "ImageDisplay.hpp"

#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>



ImageDisplay::ImageDisplay(QWidget* parent) :
    QGraphicsView(parent),
    imageItem(new QGraphicsPixmapItem())
{
    // Generate background image.
    QImage background(16, 16, QImage::Format_RGB32);
    background.fill(Qt::white);
    QColor grey(213, 213, 213);
    QPainter painter(&background);
    painter.setBrush({ grey, Qt::SolidPattern });
    painter.setPen(Qt::NoPen);
    painter.drawRect(QRect(8, 0, 8, 8));
    painter.drawRect(QRect(0, 8, 8, 8));
    painter.end();

    auto scene(new QGraphicsScene(this));
    scene->setBackgroundBrush(background);
    scene->addItem(imageItem);
    setScene(scene);
    scale(2.0, 2.0);
}



void ImageDisplay::changeImage(const QPixmap& image, const QPoint offset)
{
    imageItem->setPixmap(image);
    //imageItem->setPos(-image.width() / 2.0, -image.height() / 2.0);
    imageItem->setPos(-(image.width() - offset.x()) / 2.0, -(image.height() - offset.y()) / 2.0);
}



void ImageDisplay::clear()
{
    this->imageItem->setPixmap(QPixmap());
}
