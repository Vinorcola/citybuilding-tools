#include "AnimationController.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>



AnimationController::AnimationController(QWidget* parent) :
    QWidget(parent),
    startingImageIndexInput(new QLineEdit(this)),
    endingImageIndexInput(new QLineEdit(this))
{
    auto startButton(new QPushButton("Run", this));
    startButton->setCheckable(true);

    auto layout(new QHBoxLayout());
    layout->addWidget(startingImageIndexInput);
    layout->addWidget(endingImageIndexInput);
    layout->addWidget(startButton);
    setLayout(layout);

    connect(startButton, &QPushButton::toggled, [this](bool checked) {
        if (checked) {
            emit requiredAnimationStart(startingImageIndexInput->text().toInt(), endingImageIndexInput->text().toInt());
        }
        else {
            emit requiredAnimationEnd();
        }
    });
}
