#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <QtCore/QFileInfo>
#include <QtCore/QHash>
#include <QtGui/QImage>

class BitmapMetaData;
class ImageMetaData;

/**
 * @brief Load a displayable image using an image meta-data.
 *
 * `.sg*` files mostly contains meta-data about images and `.555` files contains the image content data. The service
 * contains all the logic necessary to load a displayable image by reading the `.555` file using the image meta-data.
 */
class ImageLoader
{
        Q_DISABLE_COPY_MOVE(ImageLoader)

    private:
        QHash<const ImageMetaData*, QImage> imageCache;

    public:
        ImageLoader();

        QImage loadImage(const ImageMetaData& imageMetaData);
        void clearCache();

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

#endif // IMAGELOADER_HPP
