#ifndef ABSTRACTIMAGEMODEL_HPP
#define ABSTRACTIMAGEMODEL_HPP

#include <QtCore/QAbstractItemModel>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>

class AbstractImageModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        AbstractImageModel(QObject* parent);

        virtual QPixmap getPixmap(const QModelIndex& index) const = 0;
        virtual QPoint getPosition(const QModelIndex& index) const = 0;
};

#endif // ABSTRACTIMAGEMODEL_HPP
