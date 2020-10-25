#include "Viewer.hpp"

#include "ImageGraphics.hpp"
#include "ImageScene.hpp"



Viewer::Viewer(QWidget* parent, ImageLoader& imageLoader) :
    QGraphicsView(parent),
    scene(new ImageScene(this)),
    image(new ImageGraphics(imageLoader))
{
    scene->addItem(image);
    setScene(scene);
}



void Viewer::changeImage(const ImageMetaData& imageMetaData)
{
    image->setVisible(true);
    image->displayImage(imageMetaData);
}



void Viewer::clear()
{
    image->setVisible(false);
}



void Viewer::changeZoom(qreal zoom)
{
    image->setScale(zoom);
}
