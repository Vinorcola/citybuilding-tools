#ifndef ABSTRACTANIMATIONMODEL_HPP
#define ABSTRACTANIMATIONMODEL_HPP

#include <QtCore/QAbstractItemModel>

class AbstractAnimationModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        virtual QPixmap getPixmap(const QModelIndex& index) const = 0;
        virtual QPoint getPosition(const QModelIndex& index) const = 0;
};

#endif // ABSTRACTANIMATIONMODEL_HPP
