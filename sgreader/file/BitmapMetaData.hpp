#ifndef BITMAPMETADATA_HPP
#define BITMAPMETADATA_HPP

#include <QtCore/QList>
#include <QtCore/QtGlobal>

class ImageMetaData;

/**
 * @brief Represente the meta-data of a bitmap.
 *
 * An `.sg*` file contains one to several bitmaps. Each bitmap contains to it tourn several images met-data.
 */
class BitmapMetaData
{
        Q_DISABLE_COPY_MOVE(BitmapMetaData)

    public:
        static const int RAW_DATA_SIZE = 200;

    private:
        struct BitmapRawData {
            Q_DISABLE_COPY_MOVE(BitmapRawData)
            char filename[65];
            char comment[51];
            quint32 width;
            quint32 height;
            quint32 num_images;
            quint32 start_index;
            quint32 end_index;
            // 4 bytes - quint32 between start & end
            // 16b, 4x int with unknown purpose
            //  8b, 2x int with (real?) width & height
            // 12b, 3x int: if any is non-zero: internal image
            // 24 more misc bytes, most zero
            quint32 unknown[16];

            explicit BitmapRawData(QDataStream& input);
        };

    private:
        BitmapRawData rawData;
        QList<ImageMetaData*> images;
        QString fileName;

    public:
        BitmapMetaData(QDataStream& input);

        void registerImage(ImageMetaData* image);

        const QString& getFileName() const;
        int getRegisteredImageQuantity() const;
        const ImageMetaData& getImageMetaData(int imageIndex) const;

        QString getTitle() const;
};

#endif // BITMAPMETADATA_HPP
