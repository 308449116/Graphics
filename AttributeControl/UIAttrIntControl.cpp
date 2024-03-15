#include "UIAttrIntControl.h"

UIAttrIntControl::UIAttrIntControl(AttributeBase *attribute, QWidget *parent)
    :UICustomIntControl(parent)
{
    setAttribute(attribute);

    if (m_attribute == nullptr)
        return;

    QObject::connect(m_attribute, &IntAttribute::valueChanged, this, &UIAttrIntControl::onAttrValueChanged);
    QObject::connect(this, &UIAttrIntControl::valueChanged, this, &UIAttrIntControl::onControlValueChanged);
}

UIAttrIntControl::~UIAttrIntControl()
{

}

// 设置属性
void UIAttrIntControl::setAttribute(AttributeBase *attribute)
{
    if (attribute == nullptr || attribute->Type() != AttributeBase::SPINBOX_TYPE)
        return;

    m_attribute = qobject_cast<IntAttribute*>(attribute);
    if (m_attribute == nullptr)
        return;

    // 设置范围
    int min = 0, max = 0;
    m_attribute->getValueRange(min, max);
    this->setRangeValue(min, max);

    // 设置值
    this->setCurrentValue(m_attribute->getValue().toInt());
    this->setTagText(m_attribute->getDisplayName());
}

void UIAttrIntControl::onAttrValueChanged(const QVariant& value)
{
    this->setCurrentValue(value.toInt());
}

void UIAttrIntControl::onControlValueChanged(int value, bool cmd)
{
    if (m_attribute->getValue().toInt() == value) {
        return;
    }
//    QObject::disconnect(m_attribute, &IntAttribute::valueChanged, this, &UIAttrIntControl::onAttrValueChanged);
    m_attribute->setValue(value, cmd);
//    QObject::connect(m_attribute, &IntAttribute::valueChanged, this, &UIAttrIntControl::onAttrValueChanged);
}
