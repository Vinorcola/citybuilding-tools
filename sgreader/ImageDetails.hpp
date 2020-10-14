#ifndef IMAGEDETAILS_HPP
#define IMAGEDETAILS_HPP

#include <QtWidgets/QWidget>

class QLabel;
class SgImage;

class ImageDetails : public QWidget
{
        Q_OBJECT

    private:
        QLabel* label;

    public:
        ImageDetails(QWidget* parent = nullptr);

        void changeImage(SgImage& image);

        void clear();
};

#endif // IMAGEDETAILS_HPP
