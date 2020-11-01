#ifndef INFODIALOG_HPP
#define INFODIALOG_HPP

#include <QtWidgets/QDialog>

/**
 * @brief A dialog with copyrights, help and licenses details.
 */
class InfoDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit InfoDialog(QWidget* parent);

    private:
        static QWidget* generateAboutTabContent(QWidget* parent);
        static QWidget* generateHelpTabContent(QWidget* parent);
        static QWidget* generateLicenseTabContent(QWidget* parent);
        static QWidget* generateGplLicenseTabContent(QWidget* parent);
        static QWidget* generateCcByLicenseTabContent(QWidget* parent);
};

#endif // INFODIALOG_HPP
