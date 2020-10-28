#include "AnimationDialog.hpp"

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>



AnimationDialog::AnimationDialog(QWidget* parent, const AbstractImageModel& model) :
    QDialog(parent),
    scene(model)
{
    auto layout(new QVBoxLayout(this));

    auto view(new QGraphicsView(&scene, this));
    layout->addWidget(view);

    auto runButton(new QPushButton("Run", this));
    runButton->setCheckable(true);
    runButton->setEnabled(scene.hasAnimation());
    connect(runButton, &QPushButton::toggled, [this](bool checked) {
        if (checked) {
            scene.startAnimation();
        }
        else {
            scene.stopAnimation();
        }
    });
    layout->addWidget(runButton);

    setLayout(layout);
}
