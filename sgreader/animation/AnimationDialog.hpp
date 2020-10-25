#ifndef ANIMATIONDIALOG_HPP
#define ANIMATIONDIALOG_HPP

#include <QtWidgets/QDialog>

#include "AnimationScene.hpp"

class AbstractAnimationModel;

class AnimationDialog : public QDialog
{
        Q_OBJECT

    private:
        AnimationScene scene;

    public:
        AnimationDialog(QWidget* parent, const AbstractAnimationModel& model);
};

#endif // ANIMATIONDIALOG_HPP
