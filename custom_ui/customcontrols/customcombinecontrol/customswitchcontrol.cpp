#include "customswitchcontrol.h"

CustomSwitchControl::CustomSwitchControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_pSwitchWidget = new CustomSwitchWidget;
    m_pMainLayout->addWidget(m_pSwitchWidget);

    m_pLabel = new QLabel;
    m_pMainLayout->addWidget(m_pLabel);

    m_pMainLayout->addStretch();

    this->setWidth(400);
    this->setHeight(30);

    QObject::connect(m_pSwitchWidget, &CustomSwitchWidget::valueChanged, \
                     this, &CustomSwitchControl::valueChanged);
}

CustomSwitchControl::~CustomSwitchControl()
{

}

// 设置/获取当前值
void CustomSwitchControl::setCurrentValue(bool isOn, bool hasAnim)
{
    m_pSwitchWidget->setSwitchStatus(isOn, hasAnim);
}

bool CustomSwitchControl::getCurrentValue()
{
    return m_pSwitchWidget->getSwitchStatus();
}

void CustomSwitchControl::setRightText(const QString& text)
{
    m_pLabel->setText(text);
}
