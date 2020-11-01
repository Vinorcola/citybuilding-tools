#ifndef FILEMODEL_HPP
#define FILEMODEL_HPP

#include <QtCore/QAbstractItemModel>
#include <QtCore/QString>
#include <QtGui/QPixmap>

class FileMetaData;
class ImageLoader;
class ImageMetaData;

/**
 * @brief A model that represent the hierarchy of available bitmaps and images withint a `.sg*` file.
 *
 * This model will be displayed in the main window's browser.
 */
class FileModel : public QAbstractItemModel
{
        Q_OBJECT

    private:
        ImageLoader& imageLoader;
        const FileMetaData& metaData;

    public:
        FileModel(QObject* parent, ImageLoader& imageLoader, const FileMetaData& metaData);

        const ImageMetaData* getImageMetaData(const QModelIndex& index) const;
        QString getTitle(const QModelIndex& index) const;
        QString getBinaryDetails(const QModelIndex& index) const;
        QPixmap getPixmap(const QModelIndex& index) const;
        QPoint getPosition(const QModelIndex& index) const;
        QPoint getRawPositionOffset(const QModelIndex& index) const;
        bool displayTile(const QModelIndex& index) const;
        bool canBeAnimated(const QModelIndex& index) const;

        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex &child) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // FILEMODEL_HPP
