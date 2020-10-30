#include "Viewer.hpp"

#include "ImageGraphics.hpp"
#include "ImageScene.hpp"



Viewer::Viewer(QWidget* parent) :
    QGraphicsView(parent),
    scene(new ImageScene(this)),
    image(new ImageGraphics())
{
    image->setVisible(false);
    scene->addItem(image);
    setScene(scene);
}



void Viewer::changeImage(const QPixmap& pixmap, const QPoint& position, bool displayTile)
{
    image->setVisible(true);
    image->displayImage(pixmap, position, displayTile);
}



void Viewer::changeImage(
    const QPixmap& pixmap,
    const QPoint& position,
    const QPixmap& foregroundPixmap,
    const QPoint& foregroundPosition,
    bool displayTile
) {
    image->setVisible(true);
    image->displaySuperimposedImages(pixmap, position, foregroundPixmap, foregroundPosition, displayTile);
}



void Viewer::clear()
{
    image->setVisible(false);
}



void Viewer::changeZoom(qreal zoom)
{
    image->setScale(zoom);
}
