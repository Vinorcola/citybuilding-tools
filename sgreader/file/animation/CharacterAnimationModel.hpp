#ifndef CHARACTERANIMATIONMODEL_HPP
#define CHARACTERANIMATIONMODEL_HPP

#include "AbstractAnimationModel.hpp"

class FileModel;

/**
 * @brief Handle a character (a dynamic element) animation.
 *
 * Character animations are composed of a set of images and may have several alternatives. Most of the time, animation
 * alternatives are due to different orientations.
 */
class CharacterAnimationModel : public AbstractAnimationModel
{
        Q_OBJECT

    private:
        QList<QList<QModelIndex>> animationImageIndexes;

    public:
        CharacterAnimationModel(QObject* parent, const FileModel& model, const QModelIndex& rootImageIndex);

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

#endif // CHARACTERANIMATIONMODEL_HPP
