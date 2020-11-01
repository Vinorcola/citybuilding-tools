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
        for (int alternativeIndex(0); alternativeIndex < animationAlternatives; ++alternativeIndex) {
            QList<QModelIndex> alternativeList;
            for (int animationIndex(0); animationIndex < imageMetaData->getAnimationLength(); ++animationIndex) {
                alternativeList.append(model.index(
                    rootImageIndex.row() + (animationIndex * animationAlternatives) + alternativeIndex,
                    rootImageIndex.column(),
                    rootImageIndex.parent()
                ));
            }
            animationImageIndexes.append(alternativeList);
        }
    }
}



QString CharacterAnimationModel::getTitle(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QString();
    }

    if (!index.parent().isValid()) {
        return tr("Alternative ") + QString::number(index.row() + 1);
    }

    if (!index.parent().parent().isValid()) {
        return QString::number(index.row() + 1);
    }

    return QString();
}



QModelIndex CharacterAnimationModel::getInitialAnimationIndex(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    if (!index.parent().isValid()) {
        return this->index(0, 0, index);
    }
    if (!index.parent().parent().isValid()) {
        return index;
    }

    return QModelIndex();
}



bool CharacterAnimationModel::hasBackgroundImage(const QModelIndex& /*index*/) const
{
    return false;
}



QModelIndex CharacterAnimationModel::getMainModelRootImageIndex() const
{
    return animationImageIndexes.first().first();
}



QModelIndex CharacterAnimationModel::getMainModelImageIndex(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    if (!index.parent().isValid()) {
        return animationImageIndexes.at(index.row()).first();
    }

    if (!index.parent().parent().isValid()) {
        return animationImageIndexes.at(index.parent().row()).at(index.row());
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
    if (!parent.parent().isValid()) {
        return animationImageIndexes.at(parent.row()).length();
    }

    return 0;
}



QModelIndex CharacterAnimationModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column, -1);
    }
    if (!parent.parent().isValid()) {
        return createIndex(row, column, parent.row());
    }

    return QModelIndex();
}



QModelIndex CharacterAnimationModel::parent(const QModelIndex& child) const
{
    if (child.internalId() >= 0) {
        return createIndex(child.internalId(), 0, -1);
    }

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
