#include "AnimationScene.hpp"

#include <QtWidgets/QGraphicsPixmapItem>

#include "AbstractAnimationModel.hpp"
#include "AnimatedImage.hpp"



AnimationScene::AnimationScene(const AbstractAnimationModel& model) :
    QGraphicsScene(),
    timerId(0),
    animatedItem(nullptr),
    animationLength(0),
    currentAnimationIndex(0)
{
    // Display root element.
    auto rootIndex(model.index(0, 0));
    auto rootPixmap(model.getPixmap(rootIndex));
    auto rootItem(new QGraphicsPixmapItem(rootPixmap));
    rootItem->setPos(0, 0);
    addItem(rootItem);

    // Check for children.
    if (model.hasChildren(rootIndex)) {
        animatedItem = new AnimatedImage();
        addItem(animatedItem);
        animationLength = model.rowCount(rootIndex);
        for (int row(0); row < animationLength; ++row) {
            auto index(model.index(row, 0, rootIndex));
            animatedItem->registerImage(model.getPixmap(index), model.getPosition(index));
        }
        animatedItem->changeAnimationImage(currentAnimationIndex);
    }
}



void AnimationScene::startAnimation()
{
    if (animationLength > 0 && animatedItem != nullptr && timerId == 0) {
        timerId = startTimer(100);
    }
}



void AnimationScene::stopAnimation()
{
    if (timerId != 0) {
        killTimer(timerId);
        timerId = 0;
    }
}



bool AnimationScene::hasAnimation() const
{
    return animationLength > 0;
}



void AnimationScene::timerEvent(QTimerEvent* /*event*/)
{
    if (animationLength > 0 && animatedItem != nullptr) {
        currentAnimationIndex = (currentAnimationIndex + 1) % animationLength;
        animatedItem->changeAnimationImage(currentAnimationIndex);
    }
}
