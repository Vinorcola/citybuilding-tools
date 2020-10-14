#include "ImageDisplay.hpp"

#include <QtWidgets/QLabel>

#include "sgimage.h"



ImageDisplay::ImageDisplay(QWidget* parent) :
    QWidget(parent),
    image(new QLabel(this))
{

}



bool ImageDisplay::changeImage(SgImage& image)
{
    auto imageFile(image.getImage());
    if (imageFile.isNull()) {
        this->image->setText(QString("Couldn't load image: %0").arg(image.errorMessage()));
        this->image->adjustSize();

        return false;
    }

    this->image->setPixmap(QPixmap::fromImage(imageFile));
    this->image->adjustSize();

    return true;
}



void ImageDisplay::clear()
{
    this->image->setPixmap(QPixmap());
}
