#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP

#include <QtWidgets/QWidget>

class QLineEdit;

class AnimationController : public QWidget
{
        Q_OBJECT

    public:
        static const int IMAGE_ANIMATION_STEP = 8;

    private:
        QLineEdit* startingImageIndexInput;
        QLineEdit* endingImageIndexInput;

    public:
        AnimationController(QWidget* parent = nullptr);

    signals:
        void requiredAnimationStart(int startingImageIndex, int endingImageIndex);

        void requiredAnimationEnd();
};

#endif // ANIMATIONCONTROLLER_HPP
