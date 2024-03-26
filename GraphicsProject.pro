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
#INCLUDEPATH += $$PWD/Common
#INCLUDEPATH += $$PWD/GraphicsObject
#INCLUDEPATH += $$PWD/UndoCmd
#INCLUDEPATH += $$PWD/Handle
#INCLUDEPATH += $$PWD/attributecontrol
#INCLUDEPATH += $$PWD/attributemodel
#INCLUDEPATH += $$PWD/attributeview
#INCLUDEPATH += $$PWD/custom_ui/
#INCLUDEPATH += $$PWD/custom_ui/customcontrols/customcombinecontrol
#INCLUDEPATH += $$PWD/custom_ui/customcontrols/customsinglecontrol

SOURCES += \
    custom_ui/customcontrols/customcombinecontrol/customcombinecontrolbase.cpp \
    custom_ui/customcontrols/customcombinecontrol/customcomboboxcontrol.cpp \
    custom_ui/customcontrols/customcombinecontrol/customdoublecontrol.cpp \
    custom_ui/customcontrols/customcombinecontrol/customgroupcontrol.cpp \
    custom_ui/customcontrols/customcombinecontrol/customintcontrol.cpp \
    custom_ui/customcontrols/customcombinecontrol/customlineeditcontrol.cpp \
    custom_ui/customcontrols/customcombinecontrol/customswitchcontrol.cpp \
    custom_ui/customcontrols/customsinglecontrol/customcombobox.cpp \
    custom_ui/customcontrols/customsinglecontrol/customdoublespinbox.cpp \
    custom_ui/customcontrols/customsinglecontrol/customintspinbox.cpp \
    custom_ui/customcontrols/customsinglecontrol/customlineedit.cpp \
    custom_ui/customcontrols/customsinglecontrol/customswitchwidget.cpp \
    custom_ui/customcontrols/customsinglecontrol/customtextedit.cpp \
    custom_ui/CustomWidgtes/customwidget.cpp \
    attributecontrol/attrboolcontrol.cpp \
    attributecontrol/attrfloatcontrol.cpp \
    attributecontrol/attrintcontrol.cpp \
    attributecontrol/attrtextcontrol.cpp \
    attributemodel/attributebase.cpp \
    attributemodel/attributegroup.cpp \
    attributemodel/boolattribute.cpp \
    attributemodel/intattribute.cpp \
    attributemodel/nodebase.cpp \
    attributemodel/nodemanager.cpp \
    attributemodel/numericattribute.cpp \
    attributemodel/positionattribute.cpp \
    attributemodel/realattribute.cpp \
    attributemodel/stringattribute.cpp \
    attributemodel/textnode.cpp \
    attributeview/attributewidget.cpp \
    attributeview/nodeattrcontrol.cpp \
    graphicsobject/graphicsabstracttemplate.cpp \
    graphicsobject/graphicsitem.cpp \
    graphicsobject/graphicsitemgroup.cpp \
    graphicsobject/graphicsitemmanager.cpp \
    graphicsobject/graphicsrectitem.cpp \
    graphicsobject/graphicstextitem.cpp \
    handle/graphicsdraghandle.cpp \
    handle/graphicshandle.cpp \
    handle/graphicslinehandle.cpp \
    handle/graphicsrotatehandle.cpp \
    handle/graphicsselection.cpp \
    handle/graphicsselectionmanager.cpp \
    handle/graphicssizehandle.cpp \
    undocmd/itemcopycmd.cpp \
    undocmd/itemcreatecmd.cpp \
    undocmd/itemdeletecmd.cpp \
    undocmd/itemgroupcmd.cpp \
    undocmd/itemmovecmd.cpp \
    undocmd/itemresizecmd.cpp \
    undocmd/itemrotatecmd.cpp \
    undocmd/itemungroupcmd.cpp \
    utils/utils.cpp \
    main.cpp \
    mainwindow.cpp \
    scenegraphics.cpp \
    viewgraphics.cpp

HEADERS += \
    custom_ui/customcontrols/customcombinecontrol/customcombinecontrolbase.h \
    custom_ui/customcontrols/customcombinecontrol/customcomboboxcontrol.h \
    custom_ui/customcontrols/customcombinecontrol/customdoublecontrol.h \
    custom_ui/customcontrols/customcombinecontrol/customgroupcontrol.h \
    custom_ui/customcontrols/customcombinecontrol/customintcontrol.h \
    custom_ui/customcontrols/customcombinecontrol/customlineeditcontrol.h \
    custom_ui/customcontrols/customcombinecontrol/customswitchcontrol.h \
    custom_ui/customcontrols/customsinglecontrol/customcombobox.h \
    custom_ui/customcontrols/customsinglecontrol/customdoublespinbox.h \
    custom_ui/customcontrols/customsinglecontrol/customintspinbox.h \
    custom_ui/customcontrols/customsinglecontrol/customlineedit.h \
    custom_ui/customcontrols/customsinglecontrol/customswitchwidget.h \
    custom_ui/customcontrols/customsinglecontrol/customtextedit.h \
    custom_ui/CustomWidgtes/customwidget.h \
    attributecontrol/attrboolcontrol.h \
    attributecontrol/attrfloatcontrol.h \
    attributecontrol/attrintcontrol.h \
    attributecontrol/attrtextcontrol.h \
    attributemodel/attributebase.h \
    attributemodel/attributegroup.h \
    attributemodel/boolattribute.h \
    attributemodel/intattribute.h \
    attributemodel/nodebase.h \
    attributemodel/nodemanager.h \
    attributemodel/numericattribute.h \
    attributemodel/positionattribute.h \
    attributemodel/realattribute.h \
    attributemodel/stringattribute.h \
    attributemodel/textnode.h \
    attributeview/attributewidget.h \
    attributeview/nodeattrcontrol.h \
    graphicsobject/graphicsabstracttemplate.h \
    graphicsobject/graphicsitem.h \
    graphicsobject/graphicsitemgroup.h \
    graphicsobject/graphicsitemmanager.h \
    graphicsobject/graphicsrectitem.h \
    graphicsobject/graphicstextitem.h \
    handle/graphicsdraghandle.h \
    handle/graphicshandle.h \
    handle/graphicslinehandle.h \
    handle/graphicsrotatehandle.h \
    handle/graphicsselection.h \
    handle/graphicsselectionmanager.h \
    handle/graphicssizehandle.h \
    undocmd/itemcopycmd.h \
    undocmd/itemcreatecmd.h \
    undocmd/itemdeletecmd.h \
    undocmd/itemgroupcmd.h \
    undocmd/itemmovecmd.h \
    undocmd/itemresizecmd.h \
    undocmd/itemrotatecmd.h \
    undocmd/itemungroupcmd.h \
    utils/utils.h \
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
