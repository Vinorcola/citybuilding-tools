#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <QtWidgets/QWidget>

class ControlPanel : public QWidget
{
        Q_OBJECT

    public:
        ControlPanel(QWidget* parent = nullptr);

    signals:
        void zoomChanged(int zoom);
};

#endif // CONTROLPANEL_HPP
