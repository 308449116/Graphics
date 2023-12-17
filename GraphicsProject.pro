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
    GraphicsObject/abstractgraphicstemplate.cpp \
    GraphicsObject/canvasitembase.cpp \
    GraphicsObject/canvasitemmanager.cpp \
    GraphicsObject/canvasrectitem.cpp \
    GraphicsObject/graphicsitem.cpp \
    GraphicsObject/graphicsrectitem.cpp \
    Handle/graphicshandle.cpp \
    Handle/graphicsselection.cpp \
    Operator/operator.cpp \
    Operator/selectoperator.cpp \
    Utils/utils.cpp \
    GraphicsObject/canvastextitem.cpp \
    main.cpp \
    mainwindow.cpp \
    GraphicsObject/scenegraphics.cpp \
    viewgraphics.cpp

HEADERS += \
    GraphicsObject/abstractgraphicstemplate.h \
    GraphicsObject/canvasitembase.h \
    GraphicsObject/canvasitemmanager.h \
    GraphicsObject/canvasrectitem.h \
    GraphicsObject/graphicsitem.h \
    GraphicsObject/graphicsrectitem.h \
    Handle/graphicshandle.h \
    Handle/graphicsselection.h \
    Operator/operator.h \
    Operator/selectoperator.h \
    Utils/utils.h \
    GraphicsObject/canvastextitem.h \
    mainwindow.h \
    GraphicsObject/scenegraphics.h \
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
