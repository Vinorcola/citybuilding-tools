#ifndef IMAGEDETAILS_HPP
#define IMAGEDETAILS_HPP

#include <QtWidgets/QWidget>

class QLabel;

class BinaryDetails : public QWidget
{
        Q_OBJECT

    private:
        QLabel* errorMessage;
        QLabel* details;

    public:
        explicit BinaryDetails(QWidget* parent = nullptr);

        void changeBinaryDetails(const QString& details);

        void setError(const QString& errorMessage);

        void clear();
};

#endif // IMAGEDETAILS_HPP
