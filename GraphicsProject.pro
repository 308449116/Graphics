QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#MOC_DIR += $$PWD/out/moc
#OBJECTS_DIR += $$PWD/out/objects
#DESTDIR += $$PWD/out/bin

#LIBS += -L$$PWD/lib -lbarcode
#INCLUDEPATH += $$PWD/include/zint
#INCLUDEPATH += $$PWD/include/barcode
INCLUDEPATH += $$PWD/Common
INCLUDEPATH += $$PWD/GraphicsObject
INCLUDEPATH += $$PWD/UndoCmd
INCLUDEPATH += $$PWD/Handle

SOURCES += \
    GraphicsObject/graphicsabstracttemplate.cpp \
    GraphicsObject/graphicsitem.cpp \
    GraphicsObject/graphicsitemgroup.cpp \
    GraphicsObject/graphicsitemmanager.cpp \
    GraphicsObject/graphicsrectitem.cpp \
    GraphicsObject/graphicstextitem.cpp \
    Handle/graphicsdraghandle.cpp \
    Handle/graphicshandle.cpp \
    Handle/graphicslinehandle.cpp \
    Handle/graphicsrotatehandle.cpp \
    Handle/graphicsselection.cpp \
    Handle/graphicsselectionmanager.cpp \
    Handle/graphicssizehandle.cpp \
    UndoCmd/itemcopycmd.cpp \
    UndoCmd/itemcreatecmd.cpp \
    UndoCmd/itemdeletecmd.cpp \
    UndoCmd/itemmovecmd.cpp \
    UndoCmd/itemresizecmd.cpp \
    UndoCmd/itemrotatecmd.cpp \
    UndoCmd/undocmdmanager.cpp \
    Utils/utils.cpp \
    main.cpp \
    mainwindow.cpp \
    scenegraphics.cpp \
    viewgraphics.cpp

HEADERS += \
    Common/common.h \
    GraphicsObject/graphicsabstracttemplate.h \
    GraphicsObject/graphicsitem.h \
    GraphicsObject/graphicsitemgroup.h \
    GraphicsObject/graphicsitemmanager.h \
    GraphicsObject/graphicsrectitem.h \
    GraphicsObject/graphicstextitem.h \
    Handle/graphicsdraghandle.h \
    Handle/graphicshandle.h \
    Handle/graphicslinehandle.h \
    Handle/graphicsrotatehandle.h \
    Handle/graphicsselection.h \
    Handle/graphicsselectionmanager.h \
    Handle/graphicssizehandle.h \
    UndoCmd/itemcopycmd.h \
    UndoCmd/itemcreatecmd.h \
    UndoCmd/itemdeletecmd.h \
    UndoCmd/itemmovecmd.h \
    UndoCmd/itemresizecmd.h \
    UndoCmd/itemrotatecmd.h \
    UndoCmd/undocmdmanager.h \
    Utils/utils.h \
    mainwindow.h \
    scenegraphics.h \
    viewgraphics.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

