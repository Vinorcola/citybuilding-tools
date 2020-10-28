#include "FileModel.hpp"

#include "BitmapMetaData.hpp"
#include "FileMetaData.hpp"
#include "ImageLoader.hpp"
#include "ImageMetaData.hpp"



FileModel::FileModel(QObject* parent, ImageLoader& imageLoader, const FileMetaData& metaData) :
    AbstractImageModel(parent),
    imageLoader(imageLoader),
    metaData(metaData)
{

}



QString FileModel::getTitle(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QString();
    }
    if (!index.parent().isValid()) {
        return metaData.getBitmapMetaData(index.row()).getTitle();
    }
    if (!index.parent().parent().isValid()) {
        return metaData.getBitmapMetaData(index.parent().row()).getImageMetaData(index.row()).getTitle();
    }

    return QString();
}



QPixmap FileModel::getPixmap(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QPixmap();
    }
    if (!index.parent().isValid()) {
        return QPixmap();
    }
    if (!index.parent().parent().isValid()) {
        return QPixmap::fromImage(imageLoader.loadImage(
            metaData.getBitmapMetaData(index.parent().row()).getImageMetaData(index.row())
        ));
    }

    return QPixmap();
}



QPoint FileModel::getPosition(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QPoint();
    }
    if (!index.parent().isValid()) {
        return QPoint();
    }
    if (!index.parent().parent().isValid()) {
        return metaData.getBitmapMetaData(index.parent().row()).getImageMetaData(index.row()).getPositionOffset();
    }

    return QPoint();
}



int FileModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 1;
}



int FileModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return metaData.getBitmapQuantity();
    }
    if (!parent.parent().isValid()) {
        return metaData.getBitmapMetaData(parent.row()).getRegisteredImageQuantity();
    }

    return 0;
}



QModelIndex FileModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column, -1);
    }
    if (!parent.parent().isValid()) {
        return createIndex(row, column, parent.row());
    }

    return QModelIndex();
}



QModelIndex FileModel::parent(const QModelIndex& child) const
{
    if (child.internalId() != static_cast<quintptr>(-1)) {
        return createIndex(child.internalId(), 0, -1);
    }

    return QModelIndex();
}



QVariant FileModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
            return getTitle(index);

        default:
            return QVariant();
    }
}
