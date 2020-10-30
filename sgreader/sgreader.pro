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
    display/image/AnimatedImageGraphics.hpp \
    display/image/ImageGraphics.hpp \
    display/image/ImageScene.hpp \
    display/image/Viewer.hpp \
    exception/FileException.hpp \
    exception/OutOfRangeException.hpp \
    exception/RuntimeException.hpp \
    file/animation/BuildingAnimationModel.hpp \
    file/AbstractImageModel.hpp \
    file/BitmapMetaData.hpp \
    file/FileMetaData.hpp \
    file/FileModel.hpp \
    file/ImageLoader.hpp \
    file/ImageMetaData.hpp \
    gui/dialog/aboutdialog.h \
    gui/dialog/helpdialog.h \
    gui/dialog/licencedialog.h \
    gui/extractWizard/filelistpage.h \
    gui/extractWizard/inputdirpage.h \
    gui/extractWizard/outputdirpage.h \
    gui/extractWizard/progresspage.h \
    gui/extractWizard/extractthread.h \
    gui/extractWizard/extractwizard.h \
    gui/ControlPanel.hpp \
    gui/ImageTree.hpp \
    gui/ImageTreeItem.hpp \
    gui/MainWindow.hpp \
    mainwindow.h \
    sgbitmap.h \
    sgfile.h \
    sgimage.h

SOURCES += \
    display/binary/BinaryDetails.cpp \
    display/binary/BinaryFormatter.cpp \
    display/image/AnimatedImageGraphics.cpp \
    display/image/ImageGraphics.cpp \
    display/image/ImageScene.cpp \
    display/image/Viewer.cpp \
    exception/FileException.cpp \
    exception/OutOfRangeException.cpp \
    exception/RuntimeException.cpp \
    file/animation/BuildingAnimationModel.cpp \
    file/AbstractImageModel.cpp \
    file/BitmapMetaData.cpp \
    file/FileMetaData.cpp \
    file/FileModel.cpp \
    file/ImageLoader.cpp \
    file/ImageMetaData.cpp \
    gui/dialog/aboutdialog.cpp \
    gui/dialog/helpdialog.cpp \
    gui/dialog/licencedialog.cpp \
    gui/extractWizard/filelistpage.cpp \
    gui/extractWizard/inputdirpage.cpp \
    gui/extractWizard/outputdirpage.cpp \
    gui/extractWizard/progresspage.cpp \
    gui/extractWizard/extractthread.cpp \
    gui/extractWizard/extractwizard.cpp \
    gui/ControlPanel.cpp \
    gui/ImageTree.cpp \
    gui/ImageTreeItem.cpp \
    gui/MainWindow.cpp \
    main.cpp \
    mainwindow.cpp \
    sgbitmap.cpp \
    sgfile.cpp \
    sgimage.cpp

RESOURCES += sgreader.qrc
RC_FILE = sgreader.rc
