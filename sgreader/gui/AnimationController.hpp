#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP

#include <QtCore/QModelIndex>
#include <QtWidgets/QAction>

class AbstractAnimationModel;

/**
 * @brief An action that controls an animation.
 *
 * This class take an animation model, and hanlde the animation display. The action allow the user to pause and play the
 * animaiton. It also have a reference to the window browser so it can enable or disable it when the animaiton is
 * running or not.
 */
class AnimationController : public QAction
{
        Q_OBJECT

    private:
        const QIcon PLAY_ICON;
        const QIcon PAUSE_ICON;

        QWidget& imageBrowser;
        const AbstractAnimationModel* model;
        QModelIndex currentIndex;
        int timerId;

    public:
        AnimationController(QWidget* parent, QWidget& imageBrowser);

        void start(const AbstractAnimationModel& model);
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
