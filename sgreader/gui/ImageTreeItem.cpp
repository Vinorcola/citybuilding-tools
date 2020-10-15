#include "ImageTreeItem.hpp"



ImageTreeItem::ImageTreeItem(QTreeWidget* parent, int id, SgImage& image) :
    QTreeWidgetItem(parent, ItemType),
    imageId(id),
    imageRecord(image)
{
    setColumnData();
}



ImageTreeItem::ImageTreeItem(QTreeWidgetItem* parent, int id, SgImage& image) :
    QTreeWidgetItem(parent, ItemType),
    imageId(id),
    imageRecord(image)
{
    setColumnData();
}



SgImage& ImageTreeItem::getImageMetadata()
{
    return imageRecord;
}



void ImageTreeItem::setColumnData()
{
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    setText(0, QString("%0: %1").arg(imageId + 1).arg(imageRecord.description()));
    setToolTip(0, imageRecord.fullDescription());
}
