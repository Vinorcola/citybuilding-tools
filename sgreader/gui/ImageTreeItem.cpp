#include "ImageTreeItem.hpp"

#include "../file/ImageMetaData.hpp"



ImageTreeItem::ImageTreeItem(
    QTreeWidget* parent,
    int imageId,
    const ImageMetaData& imageMetaData
) :
    QTreeWidgetItem(parent, ItemType),
    imageId(imageId),
    imageMetaData(imageMetaData)
{
    setColumnData();
}



ImageTreeItem::ImageTreeItem(
    QTreeWidgetItem* parent,
    int imageId,
    const ImageMetaData& imageMetaData
) :
    QTreeWidgetItem(parent, ItemType),
    imageId(imageId),
    imageMetaData(imageMetaData)
{
    setColumnData();
}



const ImageMetaData& ImageTreeItem::getImageMetaData() const
{
    return imageMetaData;
}



void ImageTreeItem::setColumnData()
{
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    setText(0, QString("%0: %1").arg(imageId + 1).arg(imageMetaData.getTitle()));
    setToolTip(0, imageMetaData.getDescription());
}
