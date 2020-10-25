#include "Animation.hpp"

#include <cassert>

#include "../file/ImageMetaData.hpp"
#include "../gui/ImageDisplay.hpp"



Animation::Animation(const BitmapMetaData& bitmapMetaData, const QList<const ImageMetaData*>& imagesMetaData) :
    bitmapMetaData(bitmapMetaData),
    imagesMetaData(imagesMetaData),
    timerId(0),
    currentImageIndex(0)
{
    assert(imagesMetaData.length() > 0);
    emit loadImage(bitmapMetaData, *imagesMetaData.first());
}



void Animation::start()
{
    if (timerId == 0) {
        timerId = startTimer(100);
    }
}



void Animation::stop()
{
    killTimer(timerId);
    timerId = 0;
}



void Animation::timerEvent(QTimerEvent* /*event*/)
{
    currentImageIndex = (currentImageIndex + 1) % imagesMetaData.length();
    emit loadImage(bitmapMetaData, *imagesMetaData.at(currentImageIndex));
}
