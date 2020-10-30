#ifndef BUILDINGANIMATIONMODEL_HPP
#define BUILDINGANIMATIONMODEL_HPP

#include <QtCore/QList>
#include <QtGui/QPixmap>

#include "AbstractAnimationModel.hpp"

class FileModel;

class BuildingAnimationModel : public AbstractAnimationModel
{
        Q_OBJECT

    private:
        QModelIndex rootImageIndex;
        QList<QModelIndex> animationImageIndexes;

    public:
        BuildingAnimationModel(QObject* parent, const FileModel& model, const QModelIndex& rootImageIndex);

        QString getTitle(const QModelIndex& index) const;
        virtual QModelIndex getMainModelRootImageIndex() const override;
        virtual QModelIndex getMainModelImageIndex(const QModelIndex& index) const override;

        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex &child) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // BUILDINGANIMATIONMODEL_HPP
