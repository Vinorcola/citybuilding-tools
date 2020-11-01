TEMPLATE = app
TARGET = SGReader
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
QT += core gui widgets

# Input
HEADERS += \
    display/binary/BinaryDetails.hpp \
    display/binary/BinaryFormatter.hpp \
    display/image/ImageGraphics.hpp \
    display/image/ImageScene.hpp \
    display/image/Viewer.hpp \
    exception/FileException.hpp \
    exception/OutOfRangeException.hpp \
    exception/RuntimeException.hpp \
    file/animation/AbstractAnimationModel.hpp \
    file/animation/BuildingAnimationModel.hpp \
    file/animation/CharacterAnimationModel.hpp \
    file/BitmapMetaData.hpp \
    file/FileMetaData.hpp \
    file/FileModel.hpp \
    file/ImageExporter.hpp \
    file/ImageLoader.hpp \
    file/ImageMetaData.hpp \
    gui/extractWizard/filelistpage.h \
    gui/extractWizard/inputdirpage.h \
    gui/extractWizard/outputdirpage.h \
    gui/extractWizard/progresspage.h \
    gui/extractWizard/extractthread.h \
    gui/extractWizard/extractwizard.h \
    gui/AnimationController.hpp \
    gui/ControlPanel.hpp \
    gui/InfoDialog.hpp \
    gui/MainWindow.hpp \
    sgbitmap.h \
    sgfile.h \
    sgimage.h

SOURCES += \
    display/binary/BinaryDetails.cpp \
    display/binary/BinaryFormatter.cpp \
    display/image/ImageGraphics.cpp \
    display/image/ImageScene.cpp \
    display/image/Viewer.cpp \
    exception/FileException.cpp \
    exception/OutOfRangeException.cpp \
    exception/RuntimeException.cpp \
    file/animation/AbstractAnimationModel.cpp \
    file/animation/BuildingAnimationModel.cpp \
    file/animation/CharacterAnimationModel.cpp \
    file/BitmapMetaData.cpp \
    file/FileMetaData.cpp \
    file/FileModel.cpp \
    file/ImageExporter.cpp \
    file/ImageLoader.cpp \
    file/ImageMetaData.cpp \
    gui/extractWizard/filelistpage.cpp \
    gui/extractWizard/inputdirpage.cpp \
    gui/extractWizard/outputdirpage.cpp \
    gui/extractWizard/progresspage.cpp \
    gui/extractWizard/extractthread.cpp \
    gui/extractWizard/extractwizard.cpp \
    gui/AnimationController.cpp \
    gui/ControlPanel.cpp \
    gui/InfoDialog.cpp \
    gui/MainWindow.cpp \
    main.cpp \
    sgbitmap.cpp \
    sgfile.cpp \
    sgimage.cpp

RESOURCES += sgreader.qrc
RC_FILE = sgreader.rc
