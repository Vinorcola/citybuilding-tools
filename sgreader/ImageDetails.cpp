#include "ImageDetails.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "sgimage.h"



ImageDetails::ImageDetails(QWidget* parent) :
    QWidget(parent),
    label(new QLabel(this))
{
    label->setFont(QFont("Courier New"));

    auto layout(new QVBoxLayout(this));
    layout->addWidget(label);
    layout->addStretch(1);

    setMinimumWidth(340);
    setLayout(layout);
}



void ImageDetails::changeImage(SgImage& image)
{
    label->setText(image.binaryDescription());
}



void ImageDetails::clear()
{
    label->setText("");
}
