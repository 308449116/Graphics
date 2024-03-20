#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class NodeBase;
class AttributeWidget : public QWidget
{
    Q_OBJECT
public:
    AttributeWidget(QWidget *parent = nullptr);
    ~AttributeWidget();

    // 设置当前显示的节点
    void setCurrentAttrNode(NodeBase *node);

private:
    QVBoxLayout *m_pMainLayout = nullptr;
    QWidget *m_pWidget = nullptr;
};

#endif
