#include "AnimationController.hpp"

#include "../file/animation/AbstractAnimationModel.hpp"

// Note: we can't initialoze the icons here as resosurces will not be loaded (images won't be found)
const QString PLAY_TEXT(QObject::tr("Play"));
const QString PAUSE_TEXT(QObject::tr("Pause"));
const int TIMER_INTERVAL(150);



AnimationController::AnimationController(QWidget* parent, QWidget* imageBrowser) :
    QAction(QIcon(":/play-icon"), PLAY_TEXT, parent),
    PLAY_ICON(":/play-icon"),
    PAUSE_ICON(":/pause-icon"),
    imageBrowser(imageBrowser),
    model(nullptr),
    currentIndex(),
    timerId(0)
{
    setEnabled(false);
    connect(this, &QAction::triggered, [this]() {
        if (timerId == 0) {
            play();
        }
        else {
            pause();
        }
    });
}



void AnimationController::start(const AbstractAnimationModel& model, const QModelIndex& initialIndex)
{
    this->model = &model;
    currentIndex = initialIndex;
    setEnabled(true);
    if (timerId == 0) {
        play();
    }
}



void AnimationController::updateCurrentIndex(const QModelIndex& index)
{
    if (timerId == 0) {
        currentIndex = index;
    }
}



void AnimationController::reset()
{
    model = nullptr;
    currentIndex = QModelIndex();
    setEnabled(false);
    if (timerId != 0) {
        pause();
    }
}



void AnimationController::play()
{
    timerId = startTimer(TIMER_INTERVAL);
    setIcon(PAUSE_ICON);
    setText(PAUSE_TEXT);
    imageBrowser->setEnabled(false);
}



void AnimationController::pause()
{
    killTimer(timerId);
    timerId = 0;
    setIcon(PLAY_ICON);
    setText(PLAY_TEXT);
    imageBrowser->setEnabled(true);
}



void AnimationController::timerEvent(QTimerEvent* /*event*/)
{
    if (model == nullptr) {
        return;
    }
    currentIndex = model->index(
        (currentIndex.row() + 1) % model->rowCount(currentIndex.parent()),
        currentIndex.column(),
        currentIndex.parent()
    );
    emit updateAnimation(currentIndex);
}
