#include "ImageMetaData.hpp"

#include <QtCore/QDataStream>

#include "../display/BinaryFormatter.hpp"



ImageMetaData::ImageMetaData(int imageId, QDataStream& input, bool includeAlpha) :
    imageId(imageId),
    rawData(input, includeAlpha),
    invertedRawData(nullptr)
{

}



void ImageMetaData::registerInvertedImage(const ImageMetaData& invertedSource)
{
    invertedRawData = &invertedSource.rawData;
}



quint8 ImageMetaData::getBitmapId() const
{
    return rawData.bitmap_id;
}



bool ImageMetaData::hasAlphaData() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.alpha_length != 0;
}



qint32 ImageMetaData::getInvertedSourceImageOffset() const
{
    return rawData.invert_offset;
}



bool ImageMetaData::isExtern() const
{
    return rawData.flags[0] != 0;
}



int ImageMetaData::getTotalDataLength() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.length + workingRawData.alpha_length;
}


int ImageMetaData::getNonAlphaDataLength() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.length;
}



int ImageMetaData::getAlphaDataLength() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.alpha_length;
}



int ImageMetaData::getBaseTileDataLength() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.base_tile_length;
}



quint32 ImageMetaData::getDataOffset() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.offset + workingRawData.flags[0]; // Somehow externals have 1 byte added to their offset
}



ImageMetaData::Type ImageMetaData::getType() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return static_cast<Type>(workingRawData.type);
}



QSize ImageMetaData::getSize() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return { workingRawData.width, workingRawData.height };
}



int ImageMetaData::getTileSize() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return workingRawData.flags[3];
}



QPoint ImageMetaData::getPositionOffset() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    switch (static_cast<Type>(workingRawData.type)) {
        case Type::Building:
            return {
                -workingRawData.width / 2,
                -workingRawData.height + 15 // 15 = half of tile height
            };

        case Type::Decoration:
            if (workingRawData.is_character) {
                return {
                    rawData.invert_offset != 0 ? -workingRawData.width + workingRawData.position_offset_x : -workingRawData.position_offset_x,
                    -workingRawData.position_offset_y + 8 // 8 = A quarter of tile height
                };
            }
            // No break wanted

        default:
            return {
                -workingRawData.width / 2,
                -workingRawData.height / 2
            };
    }
}



QString ImageMetaData::getBinaryDescription() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    QString content;
    content += rawData.invert_offset != 0 ? "inverted\n" : "normal\n";
    auto positionOffset(getPositionOffset());
    content += "{ x: " + QString::number(positionOffset.x()) + ", y:" + QString::number(positionOffset.y()) + " }\n";
    content += "------------\n";
    content += BinaryFormatter::format("offset", workingRawData.offset) + "\n";
    content += BinaryFormatter::format("length", workingRawData.length) + "\n";
    content += BinaryFormatter::format("base tile length", workingRawData.base_tile_length) + "\n";
    content += BinaryFormatter::format("__unknown_a", workingRawData.unknown_a) + "\n";
    content += BinaryFormatter::format("invert_offset", workingRawData.invert_offset) + "\n";
    content += BinaryFormatter::format("width", workingRawData.width) + "\n";
    content += BinaryFormatter::format("height", workingRawData.height) + "\n";
    content += BinaryFormatter::format("__unknown_b", workingRawData.unknown_b) + "\n";
    content += BinaryFormatter::format("__unknown_c", workingRawData.unknown_c) + "\n";
    content += BinaryFormatter::format("__unknown_d", workingRawData.unknown_d) + "\n";
    content += BinaryFormatter::format("animation length", workingRawData.image_quantity_in_animation) + "\n";
    content += BinaryFormatter::format("animation alternatives", workingRawData.animation_orientation_alternative_quantity) + "\n";
    content += BinaryFormatter::format("position offset x", workingRawData.position_offset_x) + "\n";
    content += BinaryFormatter::format("position offset y", workingRawData.position_offset_y) + "\n";
    content += BinaryFormatter::format("__unknown_e", workingRawData.unknown_e) + "\n";
    content += BinaryFormatter::format("__unknown_f", workingRawData.unknown_f) + "\n";
    content += BinaryFormatter::format("__unknown_g", workingRawData.unknown_g) + "\n";
    content += BinaryFormatter::format("__unknown_h", workingRawData.unknown_h) + "\n";
    content += BinaryFormatter::format("type", workingRawData.type) + "\n";
    content += BinaryFormatter::format("flag 1", workingRawData.flags[0]) + "\n";
    content += BinaryFormatter::format("flag 2", workingRawData.flags[1]) + "\n";
    content += BinaryFormatter::format("flag 3", workingRawData.flags[2]) + "\n";
    content += BinaryFormatter::format("tile size", workingRawData.flags[3]) + "\n";
    content += BinaryFormatter::format("bitmap_id", workingRawData.bitmap_id) + "\n";
    content += BinaryFormatter::format("__unknown_i", workingRawData.unknown_i) + "\n";
    content += BinaryFormatter::format("__unknown_j", workingRawData.unknown_j) + "\n";
    content += BinaryFormatter::format("is character", workingRawData.is_character) + "\n";
    content += BinaryFormatter::format("__unknown_l", workingRawData.unknown_l) + "\n";
    content += BinaryFormatter::format("alpha_offset", workingRawData.alpha_offset) + "\n";
    content += BinaryFormatter::format("alpha_length", workingRawData.alpha_length) + "\n";

    return content;
}



QString ImageMetaData::getTitle() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return QString::number(workingRawData.width) + 'x' + QString::number(workingRawData.height);
}



QString ImageMetaData::getDescription() const
{
    auto& workingRawData(invertedRawData == nullptr ? rawData : *invertedRawData);

    return QString("ID %7: offset %0, length %1, width %2, height %3, type %5, %6")
        .arg(workingRawData.offset)
        .arg(workingRawData.length)
        .arg(workingRawData.width)
        .arg(workingRawData.height)
        .arg(workingRawData.type)
        .arg(workingRawData.flags[0] ? "external" : "internal")
        .arg(imageId);
}



ImageMetaData::FileRawData::FileRawData(QDataStream& input, bool includeAlpha)
{
    input >> offset;
    input >> length;
    input >> base_tile_length;
    input >> unknown_a;
    input >> invert_offset;
    input >> width;
    input >> height;
    input >> unknown_b;
    input >> unknown_c;
    input >> unknown_d;
    input >> image_quantity_in_animation;
    input >> animation_orientation_alternative_quantity;
    input >> position_offset_x;
    input >> position_offset_y;
    input >> unknown_e;
    input >> unknown_f;
    input >> unknown_g;
    input >> unknown_h;
    input >> type;
    input.readRawData(flags, 4);
    input >> bitmap_id;
    input >> unknown_i;
    input >> unknown_j;
    input >> is_character;
    input >> unknown_l;

    if (includeAlpha) {
        input >> alpha_offset;
        input >> alpha_length;
    }
    else {
        alpha_offset = 0;
        alpha_length = 0;
    }
}
