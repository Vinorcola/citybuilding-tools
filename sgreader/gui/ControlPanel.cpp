#include "ControlPanel.hpp"

#include <QDebug>

#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>



ControlPanel::ControlPanel(QWidget* parent) :
    QWidget(parent)
{
    auto layout(new QHBoxLayout());

    auto zoomLabel(new QLabel("Zoom:", this));
    layout->addWidget(zoomLabel);

    auto buttonGroup(new QButtonGroup(this));
    auto zoom1(new QPushButton("x1", this));
    zoom1->setCheckable(true);
    zoom1->setChecked(true);
    buttonGroup->addButton(zoom1, 1);
    layout->addWidget(zoom1);
    auto zoom2(new QPushButton("x2", this));
    zoom2->setCheckable(true);
    buttonGroup->addButton(zoom2, 2);
    layout->addWidget(zoom2);
    auto zoom4(new QPushButton("x4", this));
    zoom4->setCheckable(true);
    buttonGroup->addButton(zoom4, 4);
    layout->addWidget(zoom4);
    connect(buttonGroup, &QButtonGroup::idToggled, [this](int id, bool checked) {
        if (checked) {
            emit zoomChanged(id);
        }
    });

    layout->addStretch(1);

    setLayout(layout);
}
