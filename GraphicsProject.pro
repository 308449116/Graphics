QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_ICONS = Agul.ico

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
INCLUDEPATH += $$PWD/AttributeControl
INCLUDEPATH += $$PWD/AttributeModel
INCLUDEPATH += $$PWD/AttributeView
INCLUDEPATH += $$PWD/CustomUI/
INCLUDEPATH += $$PWD/CustomUI/CustomControls/CustomCombineControl
INCLUDEPATH += $$PWD/CustomUI/CustomControls/CustomSingleControl

SOURCES += \
    AttributeControl/attrboolcontrol.cpp \
    AttributeControl/attrfloatcontrol.cpp \
    AttributeControl/attrintcontrol.cpp \
    AttributeControl/attrtextcontrol.cpp \
    AttributeModel/attributebase.cpp \
    AttributeModel/attributegroup.cpp \
    AttributeModel/boolattribute.cpp \
    AttributeModel/intattribute.cpp \
    AttributeModel/nodebase.cpp \
    AttributeModel/nodemanager.cpp \
    AttributeModel/numericattribute.cpp \
    AttributeModel/positionattribute.cpp \
    AttributeModel/realattribute.cpp \
    AttributeModel/stringattribute.cpp \
    AttributeModel/textnode.cpp \
    AttributeView/attributewidget.cpp \
    AttributeView/nodeattrcontrol.cpp \
    CustomUI/CustomControls/CustomCombineControl/customcombinecontrolbase.cpp \
    CustomUI/CustomControls/CustomCombineControl/customcomboboxcontrol.cpp \
    CustomUI/CustomControls/CustomCombineControl/customdoublecontrol.cpp \
    CustomUI/CustomControls/CustomCombineControl/customgroupcontrol.cpp \
    CustomUI/CustomControls/CustomCombineControl/customintcontrol.cpp \
    CustomUI/CustomControls/CustomCombineControl/customlineeditcontrol.cpp \
    CustomUI/CustomControls/CustomCombineControl/customswitchcontrol.cpp \
    CustomUI/CustomControls/CustomSingleControl/customcombobox.cpp \
    CustomUI/CustomControls/CustomSingleControl/customdoublespinbox.cpp \
    CustomUI/CustomControls/CustomSingleControl/customintspinbox.cpp \
    CustomUI/CustomControls/CustomSingleControl/customlineedit.cpp \
    CustomUI/CustomControls/CustomSingleControl/customswitchwidget.cpp \
    CustomUI/CustomControls/CustomSingleControl/customtextedit.cpp \
    CustomUI/CustomWidgtes/customwidget.cpp \
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
    UndoCmd/itemgroupcmd.cpp \
    UndoCmd/itemmovecmd.cpp \
    UndoCmd/itemresizecmd.cpp \
    UndoCmd/itemrotatecmd.cpp \
    UndoCmd/itemungroupcmd.cpp \
    Utils/utils.cpp \
    main.cpp \
    mainwindow.cpp \
    scenegraphics.cpp \
    viewgraphics.cpp

HEADERS += \
    AttributeControl/attrboolcontrol.h \
    AttributeControl/attrfloatcontrol.h \
    AttributeControl/attrintcontrol.h \
    AttributeControl/attrtextcontrol.h \
    AttributeModel/attributebase.h \
    AttributeModel/attributegroup.h \
    AttributeModel/boolattribute.h \
    AttributeModel/intattribute.h \
    AttributeModel/nodebase.h \
    AttributeModel/nodemanager.h \
    AttributeModel/numericattribute.h \
    AttributeModel/positionattribute.h \
    AttributeModel/realattribute.h \
    AttributeModel/stringattribute.h \
    AttributeModel/textnode.h \
    AttributeView/attributewidget.h \
    AttributeView/nodeattrcontrol.h \
    Common/common.h \
    CustomUI/CustomControls/CustomCombineControl/customcombinecontrolbase.h \
    CustomUI/CustomControls/CustomCombineControl/customcomboboxcontrol.h \
    CustomUI/CustomControls/CustomCombineControl/customdoublecontrol.h \
    CustomUI/CustomControls/CustomCombineControl/customgroupcontrol.h \
    CustomUI/CustomControls/CustomCombineControl/customintcontrol.h \
    CustomUI/CustomControls/CustomCombineControl/customlineeditcontrol.h \
    CustomUI/CustomControls/CustomCombineControl/customswitchcontrol.h \
    CustomUI/CustomControls/CustomSingleControl/customcombobox.h \
    CustomUI/CustomControls/CustomSingleControl/customdoublespinbox.h \
    CustomUI/CustomControls/CustomSingleControl/customintspinbox.h \
    CustomUI/CustomControls/CustomSingleControl/customlineedit.h \
    CustomUI/CustomControls/CustomSingleControl/customswitchwidget.h \
    CustomUI/CustomControls/CustomSingleControl/customtextedit.h \
    CustomUI/CustomWidgtes/customwidget.h \
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
    UndoCmd/itemgroupcmd.h \
    UndoCmd/itemmovecmd.h \
    UndoCmd/itemresizecmd.h \
    UndoCmd/itemrotatecmd.h \
    UndoCmd/itemungroupcmd.h \
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

DISTFILES += \
    CustomUI/CustomControls/CustomCombineControl/test.qmodel


