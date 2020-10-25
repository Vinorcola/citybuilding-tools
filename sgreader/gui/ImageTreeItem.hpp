#ifndef IMAGETREEITEM_H
#define IMAGETREEITEM_H

#include <QtCore/QString>
#include <QtWidgets/QTreeWidgetItem>

class ImageMetaData;

class ImageTreeItem : public QTreeWidgetItem
{
    public:
        static const int ItemType = QTreeWidgetItem::UserType;

    private:
        int imageId;
        const ImageMetaData& imageMetaData;

    public:
        ImageTreeItem(
            QTreeWidget* parent,
            int imageId,
            const ImageMetaData& imageMetaData
        );
        ImageTreeItem(
            QTreeWidgetItem* parent,
            int imageId,
            const ImageMetaData& imageMetaData
        );

        const ImageMetaData& getImageMetaData() const;

    private:
        void setColumnData();
};

#endif /* IMAGETREEITEM_H */
