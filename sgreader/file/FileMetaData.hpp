#ifndef FILEMETADATA_HPP
#define FILEMETADATA_HPP

#include <QtCore/QFileInfo>
#include <QtCore/QList>
#include <QtCore/QtGlobal>

class BitmapMetaData;
class ImageMetaData;

template<class T> using owner = T;

class FileMetaData
{
        Q_DISABLE_COPY_MOVE(FileMetaData)

    public:
        static const int HEADER_RAW_DATA_SIZE = 680;

    private:
        struct HeaderRawData {
            Q_DISABLE_COPY_MOVE(HeaderRawData)
            quint32 sg_filesize;
            quint32 version;
            quint32 unknown;
            qint32 max_image_records;
            qint32 num_image_records;
            qint32 num_bitmap_records;
            qint32 num_bitmap_records_without_system; // ?
            quint32 total_filesize;
            quint32 filesize_555;
            quint32 filesize_external;

            HeaderRawData();
        };

    private:
        QFileInfo fileInfo;
        HeaderRawData headerRawData;
        QList<owner<BitmapMetaData*>> bitmaps;
        QList<owner<ImageMetaData*>> images;

    public:
        FileMetaData(const QFileInfo& fileInfo);
        ~FileMetaData();

        const QFileInfo& getFileInfo() const;
        int getBitmapQuantity() const;
        int getTotalImageQuantity() const;
        const BitmapMetaData& getBitmapMetaData(int bitmapIndex) const;
        const ImageMetaData& getImageMetaData(int imageIndex) const;

    private:
        void loadHeaderRawData(QDataStream& input);

        bool isVersionSupported() const;
        bool isFileSizeCorrect() const;
        int getMaxBitmapsQuantity() const;
        bool doesIncludeAlpha() const;
};

#endif // FILEMETADATA_HPP
