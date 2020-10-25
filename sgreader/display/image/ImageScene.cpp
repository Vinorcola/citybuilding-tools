#include "ImageScene.hpp"

#include <QtGui/QPainter>

const int TRANSPARENT_SQUARE_SIZE(16);



ImageScene::ImageScene(QObject* parent) :
    QGraphicsScene(parent)
{
    // Generate background image.
    QImage background(TRANSPARENT_SQUARE_SIZE * 2, TRANSPARENT_SQUARE_SIZE * 2, QImage::Format_RGB32);
    background.fill(Qt::white);
    QPainter painter(&background);
    QColor grey(213, 213, 213);
    painter.setBrush({ grey, Qt::SolidPattern });
    painter.setPen(Qt::NoPen);
    painter.drawRect(QRect(TRANSPARENT_SQUARE_SIZE, 0, TRANSPARENT_SQUARE_SIZE, TRANSPARENT_SQUARE_SIZE));
    painter.drawRect(QRect(0, TRANSPARENT_SQUARE_SIZE, TRANSPARENT_SQUARE_SIZE, TRANSPARENT_SQUARE_SIZE));
    painter.end();

    setBackgroundBrush(background);
}
