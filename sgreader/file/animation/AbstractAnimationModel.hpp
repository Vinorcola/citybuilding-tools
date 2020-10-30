#ifndef ABSTRACTANIMATIONMODEL_HPP
#define ABSTRACTANIMATIONMODEL_HPP

#include <QtCore/QAbstractItemModel>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>

class AbstractAnimationModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        AbstractAnimationModel(QObject* parent);

        virtual QModelIndex getInitialSelectionIndex() const = 0;
        virtual bool hasBackgroundImage(const QModelIndex& index) const = 0;
        virtual QModelIndex getMainModelRootImageIndex() const = 0;
        virtual QModelIndex getMainModelImageIndex(const QModelIndex& index) const = 0;
};

#endif // ABSTRACTANIMATIONMODEL_HPP
