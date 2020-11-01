#ifndef ABSTRACTANIMATIONMODEL_HPP
#define ABSTRACTANIMATIONMODEL_HPP

#include <QtCore/QAbstractItemModel>
#include <QtCore/QPoint>
#include <QtGui/QPixmap>

/**
 * @brief A model handling an animation data.
 *
 * The animation models are used to run an animation. Animation information (length, alternatives) are found into the
 * first image meta data of the animation mostly (except for building images where animation info are hold by the
 * main building image).
 */
class AbstractAnimationModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        AbstractAnimationModel(QObject* parent);

        virtual int getAnimationTimeInterval() const = 0;
        virtual QModelIndex getInitialAnimationIndex(const QModelIndex& index) const = 0;
        virtual bool hasBackgroundImage(const QModelIndex& index) const = 0;
        virtual QModelIndex getMainModelRootImageIndex() const = 0;
        virtual QModelIndex getMainModelImageIndex(const QModelIndex& index) const = 0;
};

#endif // ABSTRACTANIMATIONMODEL_HPP
