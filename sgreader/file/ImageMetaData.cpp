#include "ImageMetaData.hpp"

#include <QtCore/QDataStream>



ImageMetaData::ImageMetaData(QDataStream& input, bool includeAlpha) :
    rawData()
{
    input >> rawData.offset;
    input >> rawData.length;
    input >> rawData.uncompressed_length;
    input >> rawData.unknown_a;
    input >> rawData.invert_offset;
    input >> rawData.width;
    input >> rawData.height;
    input >> rawData.unknown_b;
    input >> rawData.unknown_c;
    input >> rawData.unknown_d;
    input >> rawData.image_quantity_in_animation;
    input >> rawData.animation_orientation_alternative_quantity;
    input >> rawData.position_offset_x;
    input >> rawData.position_offset_y;
    input >> rawData.unknown_e;
    input >> rawData.unknown_f;
    input >> rawData.unknown_g;
    input >> rawData.unknown_h;
    input >> rawData.type;
    input.readRawData(rawData.flags, 4);
    input >> rawData.bitmap_id;
    input >> rawData.unknown_i;
    input >> rawData.unknown_j;
    input >> rawData.unknown_k;
    input >> rawData.unknown_l;

    if (includeAlpha) {
        input >> rawData.alpha_offset;
        input >> rawData.alpha_length;
    }
    else {
        rawData.alpha_offset = 0;
        rawData.alpha_length = 0;
    }
}



quint8 ImageMetaData::getBitmapId() const
{
    return rawData.bitmap_id;
}
