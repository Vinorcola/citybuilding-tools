#include "FileMetaData.hpp"

#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include "BitmapMetaData.hpp"
#include "ImageMetaData.hpp"



FileMetaData::FileMetaData(const QFileInfo& fileInfo) :
    fileInfo(fileInfo),
    headerRawData(),
    bitmaps(),
    images()
{
    // Create the data stream from the file.
    QFile file(fileInfo.absoluteFilePath());
    file.open(QIODevice::ReadOnly);
    QDataStream input(&file);
    input.setByteOrder(QDataStream::LittleEndian);

    // Load header raw data.
    loadHeaderRawData(input);

    if (!isVersionSupported()) {
        return;
    }
    if (!isFileSizeCorrect()) {
        return;
    }

    // Load bitmaps.
    for (int bitmapIndex(0); bitmapIndex < headerRawData.num_bitmap_records; ++bitmapIndex) {
        bitmaps.append(new BitmapMetaData(input));
    }
    file.seek(HEADER_RAW_DATA_SIZE + getMaxBitmapsQuantity() * BitmapMetaData::RAW_DATA_SIZE);

    // Load images.
    bool includeAlpha(doesIncludeAlpha());
    input.skipRawData(includeAlpha ? ImageMetaData::RAW_DATA_WITH_ALPHA_SIZE : ImageMetaData::RAW_DATA_SIZE); // Skip first image tha tis unused.
    for (int imageIndex(0); imageIndex < headerRawData.num_image_records; ++imageIndex) {
        auto image(new ImageMetaData(input, includeAlpha));
        images.append(image);
        bitmaps[image->getBitmapId()]->registerImage(image);
    }
}



FileMetaData::~FileMetaData()
{
    qDeleteAll(images);
    qDeleteAll(bitmaps);
}



void FileMetaData::loadHeaderRawData(QDataStream& input)
{
    input >> headerRawData.sg_filesize;
    input >> headerRawData.version;
    input >> headerRawData.unknown;
    input >> headerRawData.max_image_records;
    input >> headerRawData.num_image_records;
    input >> headerRawData.num_bitmap_records;
    input >> headerRawData.num_bitmap_records_without_system;
    input >> headerRawData.total_filesize;
    input >> headerRawData.filesize_555;
    input >> headerRawData.filesize_external;
    input.device()->seek(HEADER_RAW_DATA_SIZE);
}



bool FileMetaData::isVersionSupported() const
{
    switch (headerRawData.version) {
        case 0xcf: // .sg2 C3 demo
        case 0xd3: // .sg2 C3
        case 0xd5: // .sg3 Pharaoh, Zeus
        case 0xd6: // .sg3 Emperor (with alpha)
            return true;

        default:
            return false;
    }
}



bool FileMetaData::isFileSizeCorrect() const
{
    switch (headerRawData.version) {
        case 0xcf:
        case 0xd3:
            // SG2 file: filesize = 74480 or 522680 (depending on whether it's
            // a "normal" sg2 or an enemy sg2
            return headerRawData.sg_filesize == 74480 || headerRawData.sg_filesize == 522680;

        case 0xd5:
        case 0xd6:
            // SG3 file: filesize = the actual size of the sg3 file
            return headerRawData.sg_filesize == 74480 || fileInfo.size() == headerRawData.sg_filesize;

        default:
            return false;
    }
}



int FileMetaData::getMaxBitmapsQuantity() const
{
    switch (headerRawData.version) {
        case 0xcf:
            return 50;

        case 0xd3:
            return 100;

        case 0xd5:
        case 0xd6:
            return 200;

        default:
            return 0;
    }
}



bool FileMetaData::doesIncludeAlpha() const
{
    switch (headerRawData.version) {
        case 0xd6:
            return true;

        default:
            return false;
    }
}
