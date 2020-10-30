#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP

#include <QtCore/QModelIndex>
#include <QtWidgets/QAction>

class AbstractAnimationModel;

class AnimationController : public QAction
{
        Q_OBJECT

    private:
        const QIcon PLAY_ICON;
        const QIcon PAUSE_ICON;

        QWidget* imageBrowser;
        const AbstractAnimationModel* model;
        QModelIndex currentIndex;
        int timerId;

    public:
        AnimationController(QWidget* parent, QWidget* imageBrowser);

        void start(const AbstractAnimationModel& model, const QModelIndex& initialIndex);
        void updateCurrentIndex(const QModelIndex& index);
        void reset();

    signals:
        void updateAnimation(const QModelIndex& index);

    protected:
        inline void play();
        inline void pause();
        virtual void timerEvent(QTimerEvent* event);
};

#endif // ANIMATIONCONTROLLER_HPP
