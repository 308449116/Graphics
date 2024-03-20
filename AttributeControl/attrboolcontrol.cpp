#include "attrboolcontrol.h"

AttrBoolControl::AttrBoolControl(AttributeBase *attribute, QWidget *parent)
    :CustomSwitchControl(parent)
{
    setAttribute(attribute);
}

AttrBoolControl::~AttrBoolControl()
{

}

void AttrBoolControl::setAttribute(AttributeBase *attribute)
{
    if (attribute == nullptr || attribute->Type() != AttributeBase::SWITCH_TYPE)
        return;

    m_attribute = qobject_cast<BoolAttribute*>(attribute);
    this->setCurrentValue(m_attribute->getValue().toBool());
    this->setTagText(m_attribute->getDisplayName());

    QObject::connect(m_attribute, &BoolAttribute::valueChanged, this, &AttrBoolControl::onAttrValueChanged);
    QObject::connect(this, &AttrBoolControl::valueChanged, this, &AttrBoolControl::onControlValueChanged);
}

void AttrBoolControl::onAttrValueChanged(const QVariant& value)
{
    this->setCurrentValue(value.toBool(), false);
}

void AttrBoolControl::onControlValueChanged(bool value, bool cmd)
{
//    if (m_attribute->getValue().toBool() == value) {
//        return;
//    }
//    QObject::disconnect(m_attribute, &BoolAttribute::valueChanged, this, &AttrBoolControl::onAttrValueChanged);
    m_attribute->setValue(value, cmd);
//    QObject::connect(m_attribute, &BoolAttribute::valueChanged, this, &AttrBoolControl::onAttrValueChanged);
}
