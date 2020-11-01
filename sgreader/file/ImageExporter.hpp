#ifndef IMAGEEXPORTER_HPP
#define IMAGEEXPORTER_HPP

#include <QtCore/QtGlobal>

class ImageLoader;
class ImageMetaData;
class QPixmap;

class ImageExporter
{
        Q_DISABLE_COPY_MOVE(ImageExporter)

    private:
        ImageLoader& imageLoader;

    public:
        ImageExporter(ImageLoader& imageLoader);

        void exportImageTo(const ImageMetaData& image, const QString& path) const;
};

#endif // IMAGEEXPORTER_HPP
