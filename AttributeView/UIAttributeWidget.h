#ifndef UIATTRIBUTEWIDGET_H
#define UIATTRIBUTEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class NodeBase;
class UIAttributeWidget : public QWidget
{
    Q_OBJECT
public:
    UIAttributeWidget(QWidget* parent = nullptr);
    ~UIAttributeWidget();

    // 设置当前显示的节点
    void setCurrentAttrNode(NodeBase* node);

protected:
    QVBoxLayout* m_pMainLayout = nullptr;
    QWidget* m_pWidget = nullptr;
};

#endif
