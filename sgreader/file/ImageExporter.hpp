#ifndef IMAGEEXPORTER_HPP
#define IMAGEEXPORTER_HPP

#include <QtCore/QtGlobal>

class BuildingAnimationModel;
class CharacterAnimationModel;
class FileModel;
class ImageLoader;
class ImageMetaData;

class ImageExporter
{
        Q_DISABLE_COPY_MOVE(ImageExporter)

    private:
        ImageLoader& imageLoader;

    public:
        ImageExporter(ImageLoader& imageLoader);

        void exportImageTo(const ImageMetaData& image, const QString& path) const;

        void exportBuildingAnimationTo(
            const FileModel& imageModel,
            const BuildingAnimationModel& animationModel,
            const QString& path
        ) const;

        void exportCharacterAnimationTo(
            const FileModel& imageModel,
            const CharacterAnimationModel& animationModel,
            const QString& path
        ) const;
};

#endif // IMAGEEXPORTER_HPP
