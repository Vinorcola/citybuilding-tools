#include "BitmapMetaData.hpp"

#include <QtCore/QDataStream>

#include "ImageMetaData.hpp"



BitmapMetaData::BitmapMetaData(QDataStream& input) :
    rawData(),
    images()
{
    input.readRawData(rawData.filename, 65);
    rawData.filename[64] = 0; // For safety, force last character to NULL.
    input.readRawData(rawData.comment, 51);
    rawData.comment[50] = 0; // For safety, force last character to NULL.
    input >> rawData.width;
    input >> rawData.height;
    input >> rawData.num_images;
    input >> rawData.start_index;
    input >> rawData.end_index;
    for (int i(0); i < 16; ++i) {
        input >> rawData.unknown[i];
    }
}



void BitmapMetaData::registerImage(ImageMetaData* image)
{
    images.append(image);
}
