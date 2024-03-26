#ifndef NODEATTRCONTROL_H
#define NODEATTRCONTROL_H

#include <QObject>
#include <QWidget>

class NodeBase;
class AttributeBase;
class AttributeGroup;
class NodeAttrControl : public QObject
{
    Q_OBJECT

public:
    NodeAttrControl(QObject *parent = nullptr);
    ~NodeAttrControl();

    // 根据节点创建Widget
    static QWidget *createNodeWidget(NodeBase *node);

private:
    // 创建属性控件
    static QWidget *createAttributeControl(AttributeBase *attribute);

    // 创建属性组Widget
    static QWidget *createAttributeGroupControl(AttributeGroup *group);
};

#endif
