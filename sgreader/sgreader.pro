TEMPLATE = app
TARGET = SGReader
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
QT += core gui widgets

# Input
HEADERS += \
    display/BinaryFormatter.hpp \
    gui/extractWizard/filelistpage.h \
    gui/extractWizard/inputdirpage.h \
    gui/extractWizard/outputdirpage.h \
    gui/extractWizard/progresspage.h \
    gui/extractWizard/extractthread.h \
    gui/extractWizard/extractwizard.h \
    gui/ImageDetails.hpp \
    gui/ImageDisplay.hpp \
    gui/ImageTree.hpp \
    aboutdialog.h \
    helpdialog.h \
    imagetreeitem.h \
    licencedialog.h \
    mainwindow.h \
    sgbitmap.h \
    sgfile.h \
    sgimage.h

SOURCES += \
    display/BinaryFormatter.cpp \
    gui/extractWizard/filelistpage.cpp \
    gui/extractWizard/inputdirpage.cpp \
    gui/extractWizard/outputdirpage.cpp \
    gui/extractWizard/progresspage.cpp \
    gui/extractWizard/extractthread.cpp \
    gui/extractWizard/extractwizard.cpp \
    gui/ImageDetails.cpp \
    gui/ImageDisplay.cpp \
    gui/ImageTree.cpp \
    aboutdialog.cpp \
    helpdialog.cpp \
    imagetreeitem.cpp \
    licencedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    sgbitmap.cpp \
    sgfile.cpp \
    sgimage.cpp

RESOURCES += sgreader.qrc
RC_FILE = sgreader.rc
