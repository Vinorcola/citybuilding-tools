#include "BuildingAnimationModel.hpp"

#include "../BitmapMetaData.hpp"
#include "../FileModel.hpp"
#include "../ImageMetaData.hpp"



BuildingAnimationModel::BuildingAnimationModel(
    QObject* parent,
    const FileModel& model,
    const QModelIndex& rootImageIndex
) :
    AbstractAnimationModel(parent),
    rootImageIndex(rootImageIndex),
    animationImageIndexes()
{
    auto imageMetaData(model.getImageMetaData(rootImageIndex));
    if (imageMetaData) {
        for (int animationIndex(1); animationIndex <= imageMetaData->getAnimationLength(); ++animationIndex) {
            animationImageIndexes.append(model.index(
                rootImageIndex.row() + animationIndex,
                rootImageIndex.column(),
                rootImageIndex.parent()
            ));
        }
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



QModelIndex BuildingAnimationModel::getInitialSelectionIndex() const
{
    // First sub image.
    return index(0, 0, index(0, 0));
}



QModelIndex BuildingAnimationModel::getMainModelRootImageIndex() const
{
    return rootImageIndex;
}



QModelIndex BuildingAnimationModel::getMainModelImageIndex(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }
    if (!index.parent().isValid()) {
        return rootImageIndex;
    }
    if (!index.parent().parent().isValid()) {
        return animationImageIndexes.at(index.row());
    }

    return QModelIndex();
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
        return animationImageIndexes.length();
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
