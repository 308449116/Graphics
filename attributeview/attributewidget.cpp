#include "attributewidget.h"
#include "attributemodel/nodebase.h"
#include "nodeattrcontrol.h"

AttributeWidget::AttributeWidget(QWidget *parent)
    :QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    this->setMinimumWidth(100);
}

AttributeWidget::~AttributeWidget()
{

}

// 设置当前显示的节点
void AttributeWidget::setCurrentAttrNode(NodeBase *node)
{
    if (m_widget) {
        m_widget->deleteLater();
        m_widget = nullptr;
    }

    QWidget *widget = NodeAttrControl::createNodeWidget(node);
    if (widget == nullptr) {
        return;
    }

    m_widget = widget;

    // 设置Widget
    m_mainLayout->addWidget(widget);
}
