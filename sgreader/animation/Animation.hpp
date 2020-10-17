#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtGui/QPixmap>

class ImageDisplay;
class SgImage;

/**
 * This class runs an animation.
 */
class Animation : public QObject
{
        Q_OBJECT

    private:
        QList<SgImage*> images;
        ImageDisplay& display;
        int timerId;
        int currentImageIndex;

    public:
        Animation(const QList<SgImage*>& images, ImageDisplay& display);

        void start();

        void stop();

    protected:
        virtual void timerEvent(QTimerEvent* event) override;

        void updateImageDisplay();
};

#endif // ANIMATION_HPP
