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
INCLUDEPATH += $$PWD/CustomUI/CustomControls
INCLUDEPATH += $$PWD/CustomUI

SOURCES += \
    AttributeControl/UIAttrBoolControl.cpp \
    AttributeControl/UIAttrFloatControl.cpp \
    AttributeControl/UIAttrIntControl.cpp \
    AttributeControl/UIAttrTextControl.cpp \
    AttributeModel/AttributeBase.cpp \
    AttributeModel/AttributeGroup.cpp \
    AttributeModel/BoolAttribute.cpp \
    AttributeModel/IntAttribute.cpp \
    AttributeModel/NodeBase.cpp \
    AttributeModel/NodeManager.cpp \
    AttributeModel/PositionAttribute.cpp \
    AttributeModel/RealAttribute.cpp \
    AttributeModel/StringAttribute.cpp \
    AttributeModel/TextNode.cpp \
    AttributeView/UIAttributeWidget.cpp \
    AttributeView/UINodeAttrControl.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomCombineControlBase.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomComboBoxControl.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomDoubleControl.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomGroupControl.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomIntControl.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomLineEditControl.cpp \
    CustomUI/CustomControls/CustomCombineControl/UICustomSwitchControl.cpp \
    CustomUI/CustomControls/UICustomSingleControl/UICustomComboBox.cpp \
    CustomUI/CustomControls/UICustomSingleControl/UICustomDoubleSpinBox.cpp \
    CustomUI/CustomControls/UICustomSingleControl/UICustomIntSpinBox.cpp \
    CustomUI/CustomControls/UICustomSingleControl/UICustomLineEdit.cpp \
    CustomUI/CustomControls/UICustomSingleControl/UICustomSwitchWidget.cpp \
    CustomUI/CustomControls/UICustomSingleControl/UICustomTextEdit.cpp \
    CustomUI/UICustomWidgtes/CustomWidget.cpp \
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
    AttributeControl/UIAttrBoolControl.h \
    AttributeControl/UIAttrFloatControl.h \
    AttributeControl/UIAttrIntControl.h \
    AttributeControl/UIAttrTextControl.h \
    AttributeModel/AttributeBase.h \
    AttributeModel/AttributeGroup.h \
    AttributeModel/BoolAttribute.h \
    AttributeModel/IntAttribute.h \
    AttributeModel/NodeBase.h \
    AttributeModel/NodeManager.h \
    AttributeModel/PositionAttribute.h \
    AttributeModel/RealAttribute.h \
    AttributeModel/StringAttribute.h \
    AttributeModel/TextNode.h \
    AttributeView/UIAttributeWidget.h \
    AttributeView/UINodeAttrControl.h \
    Common/common.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomCombineControlBase.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomComboBoxControl.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomDoubleControl.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomGroupControl.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomIntControl.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomLineEditControl.h \
    CustomUI/CustomControls/CustomCombineControl/UICustomSwitchControl.h \
    CustomUI/CustomControls/UICustomSingleControl/UICustomComboBox.h \
    CustomUI/CustomControls/UICustomSingleControl/UICustomDoubleSpinBox.h \
    CustomUI/CustomControls/UICustomSingleControl/UICustomIntSpinBox.h \
    CustomUI/CustomControls/UICustomSingleControl/UICustomLineEdit.h \
    CustomUI/CustomControls/UICustomSingleControl/UICustomSwitchWidget.h \
    CustomUI/CustomControls/UICustomSingleControl/UICustomTextEdit.h \
    CustomUI/UICustomWidgtes/CustomWidget.h \
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


