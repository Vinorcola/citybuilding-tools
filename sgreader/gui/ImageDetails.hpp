#ifndef IMAGEDETAILS_HPP
#define IMAGEDETAILS_HPP

#include <QtWidgets/QWidget>

class QLabel;

class ImageDetails : public QWidget
{
        Q_OBJECT

    private:
        QLabel* errorMessage;
        QLabel* details;

    public:
        ImageDetails(QWidget* parent = nullptr);

        void changeImageDetails(const QString& details);

        void setError(const QString& errorMessage);

        void clear();
};

#endif // IMAGEDETAILS_HPP
