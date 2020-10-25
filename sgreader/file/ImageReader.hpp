#ifndef IMAGEREADER_HPP
#define IMAGEREADER_HPP

#include <QtCore/QFileInfo>
#include <QtCore/QHash>
#include <QtGui/QImage>

class BitmapMetaData;
class ImageMetaData;

class ImageReader
{
    private:
        QHash<const ImageMetaData*, QImage> imageCache;

    public:
        ImageReader();

        QImage readImage(const ImageMetaData& imageMetaData);

    private:
        // File loading.
        static QString resolveContentFilePath(const BitmapMetaData& bitmapMetaData, bool isImageExtern);
        static QString resolveFilePathIgnoringCase(const QDir& directory, const QString& fileName);
        // Image writing.
        // -- Load image data from file.
        static quint8* loadDataFromFile(const ImageMetaData& imageMetaData, QFile& file);
        // -- Write image from data.
        static QImage writeImage(const ImageMetaData& imageMetaData, quint8* data);
        static void writePlainImage(const ImageMetaData& imageMetaData, QImage& image, quint8* data);
        static void writeIsometricImage(const ImageMetaData& imageMetaData, QImage& image, quint8* data);
        static void writeSpriteImage(const ImageMetaData& imageMetaData, QImage& image, quint8* data);
        static void writeAlphaMask(const ImageMetaData& imageMetaData, QImage& image, const quint8* data);
        // -- Image decoding.
        static void writeIsometricBase(const ImageMetaData& imageMetaData, QImage& image, const quint8* data);
        static void writeIsometricTile(
            QImage& image,
            const quint8* data,
            int offsetX,
            int offsetY,
            int tileWidth,
            int tileHeight
        );
        static void writeTransparentImage(const ImageMetaData& imageMetaData, QImage& image, const quint8* data, int length);
        // -- Pixel decoding.
        static void writePixel(QImage& image, const QPoint& position, quint16 color);
        static void writeAlphaPixel(QImage& image, const QPoint& position, quint8 color);
};

#endif // IMAGEREADER_HPP
