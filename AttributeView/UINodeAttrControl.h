#ifndef UINODEATTRCONTROL_H
#define UINODEATTRCONTROL_H

#include "NodeBase.h"

#include <QObject>
#include <QWidget>

class AttributeBase;
class AttributeGroup;
class UINodeAttrControl : public QObject
{
    Q_OBJECT

public:
    UINodeAttrControl(QObject* parent = nullptr);
    ~UINodeAttrControl();

    // 根据节点创建Widget
    static QWidget* createNodeWidget(NodeBase* node);

private:
    // 创建属性控件
    static QWidget* createAttributeControl(AttributeBase* attribute);
    // 创建属性组Widget
    static QWidget* createAttributeGroupControl(AttributeGroup* group);
};

#endif
