#include "ImageExporter.hpp"

#include <QtCore/QDir>
#include <QtGui/QPixmap>

#include "../exception/ExportException.hpp"
#include "../file/animation/BuildingAnimationModel.hpp"
#include "../file/animation/CharacterAnimationModel.hpp"
#include "../file/FileModel.hpp"
#include "../file/ImageMetaData.hpp"
#include "ImageLoader.hpp"



ImageExporter::ImageExporter(ImageLoader& imageLoader) :
    imageLoader(imageLoader)
{

}



void ImageExporter::exportImageTo(const ImageMetaData& image, const QString& path) const
{
    imageLoader.loadImage(image).save(path.endsWith(".png") ? path : path + ".png", "PNG");
}



void ImageExporter::exportBuildingAnimationTo(
    const FileModel& imageModel,
    const BuildingAnimationModel& animationModel,
    const QString& path
) const {

    QDir().mkdir(path);
    QString manifest("building:\n");

    // Write main image.
    auto rootIndex(animationModel.index(0, 0));
    auto mainImage(imageModel.getImageMetaData(animationModel.getMainModelImageIndex(rootIndex)));
    QString animationPosition;
    if (mainImage != nullptr) {
        exportImageTo(*mainImage, path + "/main.png");
        manifest += "    mainImage: main.png\n";
        auto position(mainImage->getRawPositionOffset());
        animationPosition = "        position: { x: " + QString::number(position.x()) + ", y: " + QString::number(position.y()) + " }\n";
    }

    // Write animation images.
    auto animationLength(animationModel.rowCount(rootIndex));
    if (animationLength > 0) {
        QDir().mkdir(path + "/animation");
        manifest += "    animation:\n";
        for (int row(0); row < animationLength; ++row) {
            auto index(animationModel.index(row, 0, rootIndex));
            auto image(imageModel.getImageMetaData(animationModel.getMainModelImageIndex(index)));
            if (image != nullptr) {
                exportImageTo(*image, path + "/animation/" + QString::number(row + 1) + ".png");
                manifest += "      - file: " + QString::number(row + 1) + ".png\n";
                manifest += animationPosition;
            }
        }
    }
    else {
        manifest += "    animation: []\n";
    }

    // Write manifest.
    QFile manifestFile(path + "/manifest.yaml");
    if (!manifestFile.open(QFile::WriteOnly)) {
        throw ExportException("Could not write manifest file");
    }
    manifestFile.write(manifest.toUtf8());
}



void ImageExporter::exportCharacterAnimationTo(
    const FileModel& imageModel,
    const CharacterAnimationModel& animationModel,
    const QString& path
) const {

    QDir().mkdir(path);
    QString manifest("character:\n");

    // Write animation images.
    auto animationLength(animationModel.rowCount(animationModel.index(0, 0)));
    if (animationLength == 0) {
        throw ExportException("Try to export empty animation.");
    }

    for (int animationIndex(0), animationQuantity(animationModel.rowCount()); animationIndex < animationQuantity; ++animationIndex) {
        auto rootIndex(animationModel.index(animationIndex, 0));
        QString animationTitle("animation_" + QString::number(animationIndex + 1));
        QDir().mkdir(path + "/" + animationTitle);
        manifest += "    " + animationTitle + ":\n";

        for (int row(0); row < animationLength; ++row) {
            auto index(animationModel.index(row, 0, rootIndex));
            auto image(imageModel.getImageMetaData(animationModel.getMainModelImageIndex(index)));
            if (image != nullptr) {
                exportImageTo(*image, path + "/" + animationTitle + "/" + QString::number(row + 1) + ".png");
                manifest += "      - file: " + QString::number(row + 1) + ".png\n";
                auto position(image->getPositionOffset());
                manifest += "        position: { x: " + QString::number(position.x()) + ", y: " + QString::number(position.y()) + " }\n";
            }
        }
    }

    // Write manifest.
    QFile manifestFile(path + "/manifest.yaml");
    if (!manifestFile.open(QFile::WriteOnly)) {
        throw ExportException("Could not write manifest file");
    }
    manifestFile.write(manifest.toUtf8());
}
