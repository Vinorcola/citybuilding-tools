#include "ImageExporter.hpp"

#include <QtGui/QPixmap>

#include "ImageLoader.hpp"



ImageExporter::ImageExporter(ImageLoader& imageLoader) :
    imageLoader(imageLoader)
{

}



void ImageExporter::exportImageTo(const ImageMetaData& image, const QString& path) const
{
     imageLoader.loadImage(image).save(path.endsWith(".png") ? path : path + ".png", "PNG");
}
