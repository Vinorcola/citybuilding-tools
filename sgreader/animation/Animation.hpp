#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtGui/QPixmap>

class BitmapMetaData;
class ImageDisplay;
class ImageMetaData;

/**
 * This class runs an animation.
 */
class Animation : public QObject
{
        Q_OBJECT

    private:
        const BitmapMetaData& bitmapMetaData;
        QList<const ImageMetaData*> imagesMetaData;
        int timerId;
        int currentImageIndex;

    public:
        Animation(const BitmapMetaData& bitmapMetaData, const QList<const ImageMetaData*>& imagesMetaData);

        void start();

        void stop();

    signals:
        void loadImage(const BitmapMetaData& bitmapMetaData, const ImageMetaData& imageMetaData);

    protected:
        virtual void timerEvent(QTimerEvent* event) override;
};

#endif // ANIMATION_HPP
