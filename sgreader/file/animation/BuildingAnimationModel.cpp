#include "BuildingAnimationModel.hpp"

#include "../file/BitmapMetaData.hpp"
#include "../file/ImageLoader.hpp"
#include "../file/ImageMetaData.hpp"



BuildingAnimationModel::BuildingAnimationModel(
    QObject* parent,
    ImageLoader& imageLoader,
    const ImageMetaData& imageMetaData
) :
    AbstractImageModel(parent),
    imageLoader(imageLoader),
    animationMetaData(imageMetaData),
    rootImage(QPixmap::fromImage(imageLoader.loadImage(imageMetaData))),
    animationImages()
{
    auto& bitmapMetaData(imageMetaData.getBitmapMetaData());
    const ImageMetaData* nextImage(&imageMetaData);
    for (int animationIndex(0); animationIndex < imageMetaData.getAnimationLength(); ++animationIndex) {
        nextImage = &bitmapMetaData.getNextImage(*nextImage);
        animationImages.append(QPixmap::fromImage(imageLoader.loadImage(*nextImage)));
    }
}



QString BuildingAnimationModel::getTitle(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QString();
    }

    switch (index.internalId()) {
        case 0:
            return "Root image";

        case 1:
            return QString::number(index.row() + 1);

        default:
            return QString();
    }
}



QPixmap BuildingAnimationModel::getPixmap(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QPixmap();
    }

    switch (index.internalId()) {
        case 0:
            return rootImage;

        case 1:
            return animationImages.at(index.row());

        default:
            return QPixmap();
    }
}



QPoint BuildingAnimationModel::getPosition(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QPoint();
    }

    return animationMetaData.getRawPositionOffset();
}



bool BuildingAnimationModel::displayTile(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return false;
    }

    return true;
}



int BuildingAnimationModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 1;
}



int BuildingAnimationModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return 1;
    }
    if (!parent.parent().isValid()) {
        return animationImages.length();
    }

    return 0;
}



QModelIndex BuildingAnimationModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column, static_cast<int>(0));
    }
    if (!parent.parent().isValid()) {
        return createIndex(row, column, 1);
    }

    return QModelIndex();
}



QModelIndex BuildingAnimationModel::parent(const QModelIndex& child) const
{
    if (child.internalId() == 1) {
        return createIndex(0, 0, static_cast<int>(0));
    }

    return QModelIndex();
}



QVariant BuildingAnimationModel::data(const QModelIndex& index, int role) const
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
