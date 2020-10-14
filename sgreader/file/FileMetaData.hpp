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
    public:
        static const int HEADER_RAW_DATA_SIZE = 680;

    private:
        struct HeaderRawData {
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
        };

    private:
        QFileInfo fileInfo;
        HeaderRawData headerRawData;
        QList<owner<BitmapMetaData*>> bitmaps;
        QList<owner<ImageMetaData*>> images;

    public:
        FileMetaData(const QFileInfo& fileInfo);
        ~FileMetaData();

    private:
        void loadHeaderRawData(QDataStream& input);

        bool isVersionSupported() const;

        bool isFileSizeCorrect() const;

        int getMaxBitmapsQuantity() const;

        bool doesIncludeAlpha() const;
};

#endif // FILEMETADATA_HPP
