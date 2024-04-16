#include "customswitchcontrol.h"

CustomSwitchControl::CustomSwitchControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_switchWidget = new CustomSwitchWidget;
    m_mainLayout->addWidget(m_switchWidget);

    m_label = new QLabel;
    m_mainLayout->addWidget(m_label);

    m_mainLayout->addStretch();

    this->setWidth(400);
    this->setHeight(30);

    QObject::connect(m_switchWidget, &CustomSwitchWidget::valueChanged, \
                     this, &CustomSwitchControl::valueChanged);
}

CustomSwitchControl::~CustomSwitchControl()
{

}

// 设置/获取当前值
void CustomSwitchControl::setCurrentValue(bool isOn, bool hasAnim)
{
    m_switchWidget->setSwitchStatus(isOn, hasAnim);
}

bool CustomSwitchControl::getCurrentValue()
{
    return m_switchWidget->getSwitchStatus();
}

void CustomSwitchControl::setRightText(const QString& text)
{
    m_label->setText(text);
}
