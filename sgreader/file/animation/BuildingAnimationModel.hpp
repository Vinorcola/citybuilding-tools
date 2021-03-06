#ifndef BUILDINGANIMATIONMODEL_HPP
#define BUILDINGANIMATIONMODEL_HPP

#include <QtCore/QList>
#include <QtGui/QPixmap>

#include "AbstractAnimationModel.hpp"

class FileModel;

/**
 * @brief Handle a building (a static element) animation.
 *
 * Building animations are composed of a main image: the main building image; and an animation set of images to apply
 * over the main image.
 */
class BuildingAnimationModel : public AbstractAnimationModel
{
        Q_OBJECT

    private:
        QModelIndex rootImageIndex;
        QList<QModelIndex> animationImageIndexes;

    public:
        BuildingAnimationModel(QObject* parent, const FileModel& model, const QModelIndex& rootImageIndex);

        QString getTitle(const QModelIndex& index) const;
        virtual int getAnimationTimeInterval() const override;
        virtual QModelIndex getInitialAnimationIndex(const QModelIndex& index) const override;
        virtual bool hasBackgroundImage(const QModelIndex& index) const override;
        virtual QModelIndex getMainModelRootImageIndex() const override;
        virtual QModelIndex getMainModelImageIndex(const QModelIndex& index) const override;

        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex &child) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // BUILDINGANIMATIONMODEL_HPP
