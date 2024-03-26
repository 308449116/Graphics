#include "attributewidget.h"
#include "attributemodel/nodebase.h"
#include "nodeattrcontrol.h"

AttributeWidget::AttributeWidget(QWidget *parent)
    :QWidget(parent)
{
    m_pMainLayout = new QVBoxLayout(this);
    this->setMinimumWidth(100);
}

AttributeWidget::~AttributeWidget()
{

}

// 设置当前显示的节点
void AttributeWidget::setCurrentAttrNode(NodeBase *node)
{
    if (m_pWidget) {
        m_pWidget->deleteLater();
        m_pWidget = nullptr;
    }

    QWidget *widget = NodeAttrControl::createNodeWidget(node);
    if (widget == nullptr) {
        return;
    }

    m_pWidget = widget;

    // 设置Widget
    m_pMainLayout->addWidget(widget);
}
