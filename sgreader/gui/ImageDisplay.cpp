#include "ImageDisplay.hpp"

#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>



ImageDisplay::ImageDisplay(QWidget* parent) :
    QGraphicsView(parent),
    imageItem(new QGraphicsPixmapItem())
{
    auto scene(new QGraphicsScene(this));
    scene->addItem(imageItem);
    setScene(scene);
    scale(2.0, 2.0);
}



void ImageDisplay::changeImage(const QPixmap& image)
{
    imageItem->setPixmap(image);
    scene()->setSceneRect(imageItem->boundingRect());
}



void ImageDisplay::clear()
{
    this->imageItem->setPixmap(QPixmap());
}
