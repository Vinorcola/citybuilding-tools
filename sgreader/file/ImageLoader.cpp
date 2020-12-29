#include "ImageLoader.hpp"

#include <QtCore/QDir>

#include "../exception/FileException.hpp"
#include "BitmapMetaData.hpp"
#include "FileMetaData.hpp"
#include "ImageMetaData.hpp"



ImageLoader::ImageLoader() :
    imageCache()
{

}



QImage ImageLoader::loadImage(const ImageMetaData& imageMetaData)
{
    if (!imageCache.contains(&imageMetaData)) {
        if (imageMetaData.getTotalDataLength() == 0) {
            throw FileException("Empty image");
        }

        QFile file(resolveContentFilePath(imageMetaData.getBitmapMetaData(), imageMetaData.isExtern()));
        if (!file.open(QIODevice::ReadOnly)) {
            throw FileException("Could not open file \"" + file.fileName() + "\".");
        }

        auto data(loadDataFromFile(imageMetaData, file));

        imageCache.insert(&imageMetaData, writeImage(imageMetaData, data));
        delete[] data;
    }

    return imageCache.value(&imageMetaData);
}



void ImageLoader::clearCache()
{
    imageCache.clear();
}



QString ImageLoader::resolveContentFilePath(const BitmapMetaData& bitmapMetaData, bool isImageExtern)
{
    auto& metaDataFileInfo(bitmapMetaData.getFileMetaData().getFileInfo());
    QString fileName(
        isImageExtern ?
            bitmapMetaData.getFileName() :
            metaDataFileInfo.fileName()
    );

    // Change the extension to .555
    int position = fileName.lastIndexOf('.');
    if (position == -1) {
        throw FileException("Impossible to determine content file name for meta-data file \"" + fileName + "\".");
    }
    fileName.replace(position + 1, 3, "555");

    QDir directory(metaDataFileInfo.dir());
    QString path(resolveFilePathIgnoringCase(directory, fileName));
    if (!path.isEmpty()) {
        return path;
    }

    // Check if a "555" directory exists.
    if (directory.cd("555")) {
        path = resolveFilePathIgnoringCase(directory, fileName);
        if (!path.isEmpty()) {
            return path;
        }
    }

    throw FileException("Impossible to find content file for meta-data file \"" + fileName + "\".");
}



QString ImageLoader::resolveFilePathIgnoringCase(const QDir& directory, const QString& fileName)
{
    QString lowerFileName(fileName.toLower());

    for (auto existingFileName : directory.entryList({ fileName }, QDir::Files)) {
        if (existingFileName.toLower() == lowerFileName) {
            return directory.absoluteFilePath(existingFileName);
        }
    }

    return {};
}



quint8* ImageLoader::loadDataFromFile(const ImageMetaData& imageMetaData, QFile& file)
{
    auto imageDataLength(static_cast<unsigned int>(imageMetaData.getTotalDataLength()));
    auto data(new char[imageDataLength]);
    file.seek(imageMetaData.getDataOffset());
    auto readLength(static_cast<quint32>(file.read(data, imageDataLength)));
    if (readLength != imageDataLength) {
        if (file.atEnd() && readLength + 4 == imageDataLength) {
            // Exception for some C3 graphics: last image is 'missing' 4 bytes
            data[readLength] = 0;
            data[readLength + 1] = 0;
            data[readLength + 2] = 0;
            data[readLength + 3] = 0;
        }
        else {
            throw FileException("Could not read all the image data (missing " + QString::number(imageDataLength - readLength) + " bytes).");
        }
    }

    return reinterpret_cast<quint8*>(data);
}



QImage ImageLoader::writeImage(const ImageMetaData& imageMetaData, quint8* data)
{
    QImage image(imageMetaData.getSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    switch (imageMetaData.getType()) {
        case ImageMetaData::Type::InterfaceIcon:
        case ImageMetaData::Type::StatusIcon:
        case ImageMetaData::Type::BorderedBackground:
        case ImageMetaData::Type::InterfaceButton:
        case ImageMetaData::Type::GreySquare:
            writePlainImage(imageMetaData, image, data);
            break;

        case ImageMetaData::Type::Building:
            writeIsometricImage(imageMetaData, image, data);
            break;

        case ImageMetaData::Type::Decoration:
        case ImageMetaData::Type::Unknwon:
        case ImageMetaData::Type::Font:
            writeSpriteImage(imageMetaData, image, data);
            break;

        default:
            throw FileException("Image of unknown type: " + QString::number(static_cast<int>(imageMetaData.getType())) + ".");
    }

    if (imageMetaData.hasAlphaData()) {
        writeAlphaMask(imageMetaData, image, &data[imageMetaData.getNonAlphaDataLength()]);
    }

    if (imageMetaData.getInvertedSourceImageOffset() != 0) {
        // Flip image horizontally.
        return image.mirrored(true, false);
    }

    return image;
}



void ImageLoader::writePlainImage(const ImageMetaData& imageMetaData, QImage& image, quint8* data)
{
    // Check whether the image data is OK
    auto size(imageMetaData.getSize());
    if (size.height() * size.width() * 2 != imageMetaData.getNonAlphaDataLength()) {
        throw FileException("Image data length doesn't match image size");
    }

    int dataIndex(0);
    for (int y(0); y < size.height(); ++y) {
        for (int x(0); x < size.width(); ++x, dataIndex += 2) {
            writePixel(image, { x, y }, data[dataIndex] | (data[dataIndex + 1] << 8));
        }
    }
}



void ImageLoader::writeIsometricImage(const ImageMetaData& imageMetaData, QImage& image, quint8* data)
{
    writeIsometricBase(imageMetaData, image, data);
    writeTransparentImage(
        imageMetaData,
        image,
        &data[imageMetaData.getBaseTileDataLength()],
        imageMetaData.getNonAlphaDataLength() - imageMetaData.getBaseTileDataLength()
    );
}



void ImageLoader::writeSpriteImage(const ImageMetaData& imageMetaData, QImage& image, quint8* data)
{
    writeTransparentImage(imageMetaData, image, data, imageMetaData.getNonAlphaDataLength());
}



void ImageLoader::writeAlphaMask(const ImageMetaData& imageMetaData, QImage& image, const quint8* data)
{
    const int width(imageMetaData.getSize().width());
    const int length(imageMetaData.getAlphaDataLength());

    int dataIndex(0);
    int x(0);
    int y(0);
    while (dataIndex < length) {
        quint8 c = data[dataIndex++];
        if (c == 255) {
            // The next byte is the number of pixels to skip.
            x += data[dataIndex++];
            while (x >= width) {
                y++; x -= width;
            }
        }
        else {
            // `c' is the number of image data bytes.
            for (int j(0); j < c; j++, dataIndex++) {
                writeAlphaPixel(image, { x, y }, data[dataIndex]);
                x++;
                if (x >= width) {
                    y++; x = 0;
                }
            }
        }
    }
}



const int ISOMETRIC_TILE_WIDTH(58);
const int ISOMETRIC_TILE_HEIGHT(30);
const int ISOMETRIC_TILE_BYTES(1800);
const int ISOMETRIC_LARGE_TILE_WIDTH(78);
const int ISOMETRIC_LARGE_TILE_HEIGHT(40);
const int ISOMETRIC_LARGE_TILE_BYTES(3200);
void ImageLoader::writeIsometricBase(const ImageMetaData& imageMetaData, QImage& image, const quint8* data)
{
    const int width(imageMetaData.getSize().width());
    const int height((width + 2) / 2); // 58 -> 30, 118 -> 60, etc
    int size = imageMetaData.getTileSize();

    int tile_bytes, tile_height, tile_width;

    if (size == 0) {
        // Derive the tile size from the height (more regular than width)
        // Note that this causes a problem with 4x4 regular vs 3x3 large:
        // 4 * 30 = 120; 3 * 40 = 120 -- give precedence to regular
        if (height % ISOMETRIC_TILE_HEIGHT == 0) {
            size = height / ISOMETRIC_TILE_HEIGHT;
        }
        else if (height % ISOMETRIC_LARGE_TILE_HEIGHT == 0) {
            size = height / ISOMETRIC_LARGE_TILE_HEIGHT;
        }
    }
    if (size == 0) {
        throw FileException("Unknown isometric tile size: height " + QString::number(height));
    }

    // Determine whether we should use the regular or large (emperor) tiles
    if (ISOMETRIC_TILE_HEIGHT * size == height) {
        // Regular tile
        tile_bytes  = ISOMETRIC_TILE_BYTES;
        tile_height = ISOMETRIC_TILE_HEIGHT;
        tile_width  = ISOMETRIC_TILE_WIDTH;
    }
    else if (ISOMETRIC_LARGE_TILE_HEIGHT * size == height) {
        // Large (emperor) tile
        tile_bytes  = ISOMETRIC_LARGE_TILE_BYTES;
        tile_height = ISOMETRIC_LARGE_TILE_HEIGHT;
        tile_width  = ISOMETRIC_LARGE_TILE_WIDTH;
    }
    else {
        throw FileException(
            QString("Unknown tile size: % (height %1, width %2, size %3)")
                .arg(2 * height / size)
                .arg(height)
                .arg(width)
                .arg(size)
        );
    }

    // Check if buffer length is enough: (width + 2) * height / 2 * 2bpp
    if ((width + 2) * height != imageMetaData.getBaseTileDataLength()) {
        throw FileException(
            QString("Data length doesn't match footprint size: %0 vs %1 (%2) %3")
                .arg((width + 2) * height)
                .arg(imageMetaData.getBaseTileDataLength())
                .arg(imageMetaData.getNonAlphaDataLength())
                .arg(imageMetaData.getInvertedSourceImageOffset())
        );
    }

    int dataIndex(0);
    int y_offset(imageMetaData.getSize().height() - height);
    for (int y(0); y < (size + (size - 1)); y++) {
        int x_offset((y < size ? (size - y - 1) : (y - size + 1)) * tile_height);
        for (int x(0); x < (y < size ? y + 1 : 2 * size - y - 1); x++, dataIndex++) {
            writeIsometricTile(image, &data[dataIndex * tile_bytes], x_offset, y_offset, tile_width, tile_height);
            x_offset += tile_width + 2;
        }
        y_offset += tile_height / 2;
    }
}



void ImageLoader::writeIsometricTile(QImage& image, const quint8* data, int offsetX, int offsetY, int tileWidth, int tileHeight)
{
    const int halfHeight(tileHeight / 2);

    int dataIndex(0);
    for (int y(0); y < halfHeight; y++) {
        const int start(tileHeight - 2 * (y + 1));
        const int end(tileWidth - start);
        for (int x(start); x < end; x++, dataIndex += 2) {
            writePixel(image, { offsetX + x, offsetY + y }, (data[dataIndex + 1] << 8) | data[dataIndex]);
        }
    }
    for (int y(halfHeight); y < tileHeight; y++) {
        const int start(2 * y - tileHeight);
        const int end(tileWidth - start);
        for (int x(start); x < end; x++, dataIndex += 2) {
            writePixel(image, { offsetX + x, offsetY + y }, (data[dataIndex + 1] << 8) | data[dataIndex]);
        }
    }
}



void ImageLoader::writeTransparentImage(const ImageMetaData& imageMetaData, QImage& image, const quint8* data, int length)
{
    const bool transformRedToTransparent(
        !imageMetaData.hasAlphaData() && imageMetaData.getType() == ImageMetaData::Type::Decoration
    );
    const int width(imageMetaData.getSize().width());

    int dataIndex(0);
    int x(0), y(0);
    while (dataIndex < length) {
        quint8 c = data[dataIndex++];
        if (c == 255) {
            // The next byte is the number of pixels to skip
            x += data[dataIndex++];
            while (x >= width) {
                y++; x -= width;
            }
        }
        else {
            // `c' is the number of image data bytes
            for (int j(0); j < c; j++, dataIndex += 2) {
                writePixel(image, { x, y }, data[dataIndex] | (data[dataIndex+1] << 8), transformRedToTransparent);
                x++;
                if (x >= width) {
                    y++; x = 0;
                }
            }
        }
    }
}



void ImageLoader::writePixel(QImage& image, const QPoint& position, quint16 color, bool transformRedToTransparent)
{
    if (color == 0xf81f) {
        // ???
        return;
    }

    quint32 rgb = 0xff000000;

    // Red: bits 11-15, should go to bits 17-24
    rgb |= ((color & 0x7c00) << 9) | ((color & 0x7000) << 4);

    // Green: bits 6-10, should go to bits 9-16
    rgb |= ((color & 0x3e0) << 6) | ((color & 0x300));

    // Blue: bits 1-5, should go to bits 1-8
    rgb |= ((color & 0x1f) << 3) | ((color & 0x1c) >> 2);

    // Transform red to transparent black (for shadows).
    if (rgb == 0xffff0000 && transformRedToTransparent) {
        rgb = 0x66000000;
    }

    image.setPixel(position, rgb);
}



void ImageLoader::writeAlphaPixel(QImage& image, const QPoint& position, quint8 color)
{
    /* Only the first five bits of the alpha channel are used */
    quint8 alpha = ((color & 0x1f) << 3) | ((color & 0x1c) >> 2);

    image.setPixel(position, (alpha << 24) | (image.pixel(position) & 0xffffff));
}
