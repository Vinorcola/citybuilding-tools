#ifndef BUILDINGANIMATIONMODEL_HPP
#define BUILDINGANIMATIONMODEL_HPP

#include <QtCore/QList>
#include <QtGui/QPixmap>

#include "../file/AbstractImageModel.hpp"

class BitmapMetaData;
class FileMetaData;
class ImageLoader;
class ImageMetaData;

class BuildingAnimationModel : public AbstractImageModel
{
        Q_OBJECT

    private:
        ImageLoader& imageLoader;
        const ImageMetaData& animationMetaData;
        QPixmap rootImage;
        QList<QPixmap> animationImages;

    public:
        BuildingAnimationModel(QObject* parent, ImageLoader& imageLoader, const ImageMetaData& imageMetaData);

        QString getTitle(const QModelIndex& index) const;
        virtual QPixmap getPixmap(const QModelIndex &index) const override;
        virtual QPoint getPosition(const QModelIndex &index) const override;

        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex &child) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // BUILDINGANIMATIONMODEL_HPP
