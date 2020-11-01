#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <QtWidgets/QWidget>

/**
 * @brief A panel for controling the display zoom.
 */
class ControlPanel : public QWidget
{
        Q_OBJECT

    public:
        explicit ControlPanel(QWidget* parent = nullptr);

    signals:
        void zoomChanged(int zoom);
};

#endif // CONTROLPANEL_HPP
