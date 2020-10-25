#include "BitmapMetaData.hpp"

#include <QtCore/QDataStream>

#include "../exception/OutOfRangeException.hpp"
#include "ImageMetaData.hpp"



BitmapMetaData::BitmapMetaData(QDataStream& input) :
    rawData(input),
    images(),
    fileName(rawData.filename)
{

}



void BitmapMetaData::registerImage(ImageMetaData* image)
{
    images.append(image);
}



const QString& BitmapMetaData::getFileName() const
{
    return fileName;
}



int BitmapMetaData::getRegisteredImageQuantity() const
{
    return images.count();
}



const ImageMetaData& BitmapMetaData::getImageMetaData(int imageIndex) const
{
    return *images.at(imageIndex);
}



const ImageMetaData& BitmapMetaData::getNextImage(const ImageMetaData& from) const
{
    for (auto iterator(images.begin()), end(images.end()); iterator != end; ++iterator) {
        if (*iterator == &from) {
            ++iterator;
            if (iterator != end) {
                return **iterator;
            }
        }
    }

    throw OutOfRangeException("Cannot find next image in bitmap.");
}



QString BitmapMetaData::getTitle() const
{
    return fileName + " (" + QString::number(images.length()) + ")";
}



BitmapMetaData::BitmapRawData::BitmapRawData(QDataStream& input)
{
    input.readRawData(filename, 65);
    filename[64] = 0; // For safety, force last character to null char.
    input.readRawData(comment, 51);
    comment[50] = 0; // For safety, force last character to null char.
    input >> width;
    input >> height;
    input >> num_images;
    input >> start_index;
    input >> end_index;
    for (int i(0); i < 16; ++i) {
        input >> unknown[i];
    }
}
