#include "CharacterAnimationModel.hpp"

#include "../BitmapMetaData.hpp"
#include "../FileModel.hpp"
#include "../ImageMetaData.hpp"



CharacterAnimationModel::CharacterAnimationModel(
    QObject* parent,
    const FileModel& model,
    const QModelIndex& rootImageIndex
) :
    AbstractAnimationModel(parent),
    animationImageIndexes()
{
    auto imageMetaData(model.getImageMetaData(rootImageIndex));
    if (imageMetaData) {
        auto animationAlternatives(imageMetaData->getAnimationAlternativesQuantity());
        if (animationAlternatives == 0) {
            animationAlternatives = 1;
        }
        animationImageIndexes.append(rootImageIndex);
        for (int animationIndex(1); animationIndex < imageMetaData->getAnimationLength(); ++animationIndex) {
            animationImageIndexes.append(model.index(
                rootImageIndex.row() + (animationIndex * animationAlternatives),
                rootImageIndex.column(),
                rootImageIndex.parent()
            ));
        }
    }
}



QString CharacterAnimationModel::getTitle(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QString();
    }

    if (!index.parent().isValid()) {
        return QString::number(index.row() + 1);
    }

    return QString();
}



QModelIndex CharacterAnimationModel::getInitialSelectionIndex() const
{
    return index(0, 0);
}



bool CharacterAnimationModel::hasBackgroundImage(const QModelIndex& /*index*/) const
{
    return false;
}



QModelIndex CharacterAnimationModel::getMainModelRootImageIndex() const
{
    return animationImageIndexes.first();
}



QModelIndex CharacterAnimationModel::getMainModelImageIndex(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    if (!index.parent().isValid()) {
        return animationImageIndexes.at(index.row());
    }

    return QModelIndex();
}



int CharacterAnimationModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 1;
}



int CharacterAnimationModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return animationImageIndexes.length();
    }

    return 0;
}



QModelIndex CharacterAnimationModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column);
    }

    return QModelIndex();
}



QModelIndex CharacterAnimationModel::parent(const QModelIndex& /*child*/) const
{
    return QModelIndex();
}



QVariant CharacterAnimationModel::data(const QModelIndex& index, int role) const
{
    switch (role) {
        case Qt::DisplayRole:
            return getTitle(index);

        default:
            return QVariant();
    }
}
