QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
MOC_DIR += $$PWD/out/moc
OBJECTS_DIR += $$PWD/out/objects
DESTDIR += $$PWD/out/bin

#LIBS += -L$$PWD/lib -lbarcode
#INCLUDEPATH += $$PWD/include/zint
#INCLUDEPATH += $$PWD/include/barcode

SOURCES += \
    graphicsabstracttemplate.cpp \
    graphicsdraghandle.cpp \
    graphicsitem.cpp \
    graphicsrectitem.cpp \
    graphicshandle.cpp \
    graphicsrotatehandle.cpp \
    graphicsselection.cpp \
    graphicsselectionmanager.cpp \
    graphicssizehandle.cpp \
    Utils/utils.cpp \
    graphicstextitem.cpp \
    main.cpp \
    mainwindow.cpp \
    scenegraphics.cpp \
    viewgraphics.cpp

HEADERS += \
    graphicsabstracttemplate.h \
    graphicsdraghandle.h \
    graphicsitem.h \
    graphicsrectitem.h \
    graphicshandle.h \
    graphicsrotatehandle.h \
    graphicsselection.h \
    graphicsselectionmanager.h \
    graphicssizehandle.h \
    Utils/utils.h \
    graphicstextitem.h \
    mainwindow.h \
    scenegraphics.h \
    viewgraphics.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Utils/Utils.pro

RESOURCES += \
    res.qrc
