#ifndef IMAGEMETADATA_HPP
#define IMAGEMETADATA_HPP

#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QtGlobal>

class BitmapMetaData;

/**
 * @brief Represent the meta-data of an image.
 *
 * The meta-data are extracted from the `.sg*` file. They mainly indicate the location of the image in the `.555` file.
 * Depending of the SG version, the meta-data are stored on 64 or 72 bytes. Last version contains alpha information.
 */
class ImageMetaData
{
        Q_DISABLE_COPY_MOVE(ImageMetaData)

    public:
        static const int RAW_DATA_SIZE = 64;
        static const int RAW_DATA_WITH_ALPHA_SIZE = 72;

        enum class Type {
            InterfaceIcon = 0,
            StatusIcon = 1,
            BorderedBackground = 10,
            InterfaceButton = 12,
            GreySquare = 13,
            Building = 30,
            Decoration = 256,
            Unknwon = 257,
            Font = 276,
        };

    private:
        struct FileRawData {
            Q_DISABLE_COPY_MOVE(FileRawData)
            quint32 offset;
            quint32 length;
            quint32 base_tile_length;
            quint32 unknown_a; // 4 zero bytes
            qint32 invert_offset;
            qint16 width;
            qint16 height;
            qint16 unknown_b; // Unknown short
            qint16 unknown_c; // Unknown short
            quint16 unknown_d; // 22 unknown bytes, mostly zero
            quint16 image_quantity_in_animation;
            quint16 animation_orientation_alternative_quantity;
            qint16 position_offset_x;
            qint16 position_offset_y;
            quint16 unknown_e;
            quint32 unknown_f;
            quint32 unknown_g;
            quint16 unknown_h;
            quint16 type;
            char flags[4]; // 4 flag/option-like bytes
            quint8 bitmap_id;
            quint8 unknown_i; // 3 bytes
            quint8 unknown_j;
            quint8 is_character;
            quint32 unknown_l; // 4 zero bytes
            // For D6 and up SG3 versions: alpha masks
            quint32 alpha_offset;
            quint32 alpha_length;

            FileRawData(QDataStream& input, bool includeAlpha);
        };

    private:
        FileRawData rawData;
        const BitmapMetaData& bitmapMetaData;
        int imageId;
        const FileRawData* invertedRawData; // Some image are the vertical flip of other images. This is the raw data of the inverted source image.

    public:
        ImageMetaData(const QList<BitmapMetaData*> bitmaps, int imageId, QDataStream& input, bool includeAlpha);

        void registerInvertedImage(const ImageMetaData& invertedSource);

        const BitmapMetaData& getBitmapMetaData() const;
        quint8 getBitmapId() const;
        bool hasAlphaData() const;
        qint32 getInvertedSourceImageOffset() const;
        bool isExtern() const;
        int getTotalDataLength() const;
        int getNonAlphaDataLength() const;
        int getAlphaDataLength() const;
        int getBaseTileDataLength() const;
        quint32 getDataOffset() const;
        Type getType() const;
        QSize getSize() const;
        int getTileSize() const;
        QPoint getPositionOffset() const;
        QPoint getRawPositionOffset() const;
        QString getBinaryDescription() const;
        int getAnimationLength() const;
        bool isBuilding() const;
        bool isCharacter() const;

        QString getTitle() const;
        QString getDescription() const;
};

#endif // IMAGEMETADATA_HPP
