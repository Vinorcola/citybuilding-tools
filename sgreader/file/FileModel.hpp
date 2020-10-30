#ifndef FILEMODEL_HPP
#define FILEMODEL_HPP

#include "AbstractImageModel.hpp"

class FileMetaData;
class ImageLoader;

class FileModel : public AbstractImageModel
{
        Q_OBJECT

    private:
        ImageLoader& imageLoader;
        const FileMetaData& metaData;

    public:
        FileModel(QObject* parent, ImageLoader& imageLoader, const FileMetaData& metaData);

        QString getTitle(const QModelIndex& index) const;
        virtual QPixmap getPixmap(const QModelIndex& index) const override;
        virtual QPoint getPosition(const QModelIndex& index) const override;
        virtual bool displayTile(const QModelIndex& index) const override;
        bool canBeAnimated(const QModelIndex& index) const;

        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex &child) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // FILEMODEL_HPP
