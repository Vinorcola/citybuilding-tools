#ifndef IMAGEDISPLAY_HPP
#define IMAGEDISPLAY_HPP

#include <QtWidgets/QWidget>

class QLabel;
class SgImage;

class ImageDisplay : public QWidget
{
        Q_OBJECT

    private:
        QLabel* image;

    public:
        ImageDisplay(QWidget* parent = nullptr);

        bool changeImage(SgImage& image);

        void clear();
};

#endif // IMAGEDISPLAY_HPP
