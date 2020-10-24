TEMPLATE = app
TARGET = SGReader
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
QT += core gui widgets

# Input
HEADERS += \
    animation/Animation.hpp \
    display/BinaryFormatter.hpp \
    exception/FileException.hpp \
    file/BitmapMetaData.hpp \
    file/FileMetaData.hpp \
    file/ImageMetaData.hpp \
    file/ImageReader.hpp \
    gui/AnimationController.hpp \
    gui/dialog/aboutdialog.h \
    gui/dialog/helpdialog.h \
    gui/dialog/licencedialog.h \
    gui/extractWizard/filelistpage.h \
    gui/extractWizard/inputdirpage.h \
    gui/extractWizard/outputdirpage.h \
    gui/extractWizard/progresspage.h \
    gui/extractWizard/extractthread.h \
    gui/extractWizard/extractwizard.h \
    gui/ImageDetails.hpp \
    gui/ImageDisplay.hpp \
    gui/ImageTree.hpp \
    gui/ImageTreeItem.hpp \
    mainwindow.h \
    sgbitmap.h \
    sgfile.h \
    sgimage.h

SOURCES += \
    animation/Animation.cpp \
    display/BinaryFormatter.cpp \
    exception/FileException.cpp \
    file/BitmapMetaData.cpp \
    file/FileMetaData.cpp \
    file/ImageMetaData.cpp \
    file/ImageReader.cpp \
    gui/AnimationController.cpp \
    gui/dialog/aboutdialog.cpp \
    gui/dialog/helpdialog.cpp \
    gui/dialog/licencedialog.cpp \
    gui/extractWizard/filelistpage.cpp \
    gui/extractWizard/inputdirpage.cpp \
    gui/extractWizard/outputdirpage.cpp \
    gui/extractWizard/progresspage.cpp \
    gui/extractWizard/extractthread.cpp \
    gui/extractWizard/extractwizard.cpp \
    gui/ImageDetails.cpp \
    gui/ImageDisplay.cpp \
    gui/ImageTree.cpp \
    gui/ImageTreeItem.cpp \
    main.cpp \
    mainwindow.cpp \
    sgbitmap.cpp \
    sgfile.cpp \
    sgimage.cpp

RESOURCES += sgreader.qrc
RC_FILE = sgreader.rc
