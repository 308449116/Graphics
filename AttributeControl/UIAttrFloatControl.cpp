#include "UIAttrFloatControl.h"
#include <QDebug>

UIAttrFloatControl::UIAttrFloatControl(AttributeBase *attribute, QWidget *parent)
    :UICustomDoubleControl(parent)
{
    setAttribute(attribute);

    if (m_attribute == nullptr)
        return;

    QObject::connect(m_attribute, &RealAttribute::valueChanged, this, &UIAttrFloatControl::onValueChanged);
    QObject::connect(this, &UIAttrFloatControl::valueChanged, this, &UIAttrFloatControl::onControlValueChanged);
}

UIAttrFloatControl::~UIAttrFloatControl()
{

}

void UIAttrFloatControl::setAttribute(AttributeBase *attribute)
{
    if (attribute == nullptr || attribute->Type() != AttributeBase::DOUBLESPINBOX_TYPE)
        return;

    m_attribute = qobject_cast<RealAttribute*>(attribute);
    if (m_attribute == nullptr)
        return;

    // 设置范围
    qreal startValue, endValue;
    m_attribute->getValueRange(startValue, endValue);
    this->setRangeValue(startValue, endValue);

    // 设置值
    this->setCurrentValue(m_attribute->getValue().toDouble());
    this->setTagText(m_attribute->getDisplayName());
}

void UIAttrFloatControl::onValueChanged(const QVariant& value)
{
    this->setCurrentValue(value.toDouble());
}

void UIAttrFloatControl::onControlValueChanged(qreal value, bool cmd)
{
//    if (m_attribute->getValue().toDouble() == value) {
//        return;
//    }

//    QObject::disconnect(m_attribute, &RealAttribute::valueChanged, this, &UIAttrFloatControl::onValueChanged);
    m_attribute->setValue(value, cmd);
//    QObject::connect(m_attribute, &RealAttribute::valueChanged, this, &UIAttrFloatControl::onValueChanged);
}
