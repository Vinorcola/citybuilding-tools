#include "Animation.hpp"

#include <cassert>

#include "../gui/ImageDisplay.hpp"
#include "../sgimage.h"



Animation::Animation(const QList<SgImage*>& images, ImageDisplay& display) :
    images(images),
    display(display),
    timerId(0),
    currentImageIndex(0)
{
    assert(images.length() > 0);
    updateImageDisplay();
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
    currentImageIndex = (currentImageIndex + 1) % images.length();
    updateImageDisplay();
}



void Animation::updateImageDisplay()
{
    auto image(images.at(currentImageIndex));
    display.changeImage(QPixmap::fromImage(image->getImage()), image->getPositionOffset());
}
