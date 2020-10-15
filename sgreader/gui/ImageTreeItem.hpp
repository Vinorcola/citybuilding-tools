#ifndef IMAGETREEITEM_H
#define IMAGETREEITEM_H

#include <QtCore/QString>
#include <QtWidgets/QTreeWidgetItem>

#include "../sgimage.h"



class ImageTreeItem : public QTreeWidgetItem
{
    public:
        static const int ItemType = QTreeWidgetItem::UserType;

    private:
        int imageId;
        SgImage& imageRecord;

    public:
        ImageTreeItem(QTreeWidget* parent, int id, SgImage& image);
        ImageTreeItem(QTreeWidgetItem* parent, int id, SgImage& image);

        SgImage& getImageMetadata();

    private:
        void setColumnData();
};

#endif /* IMAGETREEITEM_H */
