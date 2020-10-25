#ifndef ANIMATIONSCENE_HPP
#define ANIMATIONSCENE_HPP

#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsScene>

class AbstractAnimationModel;
class AnimatedImageGraphics;

class AnimationScene : public QGraphicsScene
{
        Q_OBJECT

    private:
        int timerId;
        AnimatedImageGraphics* animatedItem;
        int animationLength;
        int currentAnimationIndex;

    public:
        AnimationScene(const AbstractAnimationModel& model);

        void startAnimation();
        void stopAnimation();

        bool hasAnimation() const;

    protected:
        virtual void timerEvent(QTimerEvent* event) override;
};

#endif // ANIMATIONSCENE_HPP
