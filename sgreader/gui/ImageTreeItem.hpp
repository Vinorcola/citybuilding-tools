#ifndef IMAGETREEITEM_H
#define IMAGETREEITEM_H

#include <QtCore/QString>
#include <QtWidgets/QTreeWidgetItem>

class BitmapMetaData;
class ImageMetaData;

class ImageTreeItem : public QTreeWidgetItem
{
    public:
        static const int ItemType = QTreeWidgetItem::UserType;

    private:
        int imageId;
        const BitmapMetaData& bitmapMetaData;
        const ImageMetaData& imageMetaData;

    public:
        ImageTreeItem(
            QTreeWidget* parent,
            const BitmapMetaData& bitmapMetaData,
            int imageId,
            const ImageMetaData& imageMetaData
        );
        ImageTreeItem(
            QTreeWidgetItem* parent,
            const BitmapMetaData& bitmapMetaData,
            int imageId,
            const ImageMetaData& imageMetaData
        );

        const BitmapMetaData& getBitmapMetaData() const;
        const ImageMetaData& getImageMetaData() const;

    private:
        void setColumnData();
};

#endif /* IMAGETREEITEM_H */
