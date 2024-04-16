#include "attrintcontrol.h"
#include "attributemodel/numericattribute.h"

AttrIntControl::AttrIntControl(AttributeBase *attribute, QWidget *parent)
    :CustomIntControl(parent)
{
    setAttribute(attribute);
}

AttrIntControl::~AttrIntControl()
{

}

// 设置属性
void AttrIntControl::setAttribute(AttributeBase *attribute)
{
    if (attribute == nullptr || attribute->Type() != AttributeBase::SPINBOX_TYPE) {
        return;
    }

    m_attribute = qobject_cast<IntAttribute*>(attribute);
    if (m_attribute == nullptr) {
        return;
    }

    // 设置范围
    int min = 0, max = 0;
    m_attribute->getValueRange(min, max);
    this->setRangeValue(min, max);

    // 设置值
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    onSuffixTypeChanged(numericAttr->suffixType());
//    this->setCurrentValue(m_attribute->getValue().toInt());
    this->setTagText(m_attribute->getDisplayName());
    this->setEnabled(m_attribute->isEnable());

    //设置是否使能
    setEnabled(m_attribute->isEnable());

    QObject::connect(m_attribute, &IntAttribute::valueChanged, this, &AttrIntControl::onAttrValueChanged);
//    QObject::connect(m_attribute, &IntAttribute::enabledChanged, this, &AttrIntControl::onEnableChanged);
    QObject::connect(this, &AttrIntControl::valueChanged, this, &AttrIntControl::onControlValueChanged);
    QObject::connect(numericAttr, &NumericAttribute::suffixTypeChanged, this, &AttrIntControl::onSuffixTypeChanged);
}

void AttrIntControl::onAttrValueChanged(const QVariant& value)
{
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    int newValue = NumericAttribute::convertFormPixels(value.toInt(), numericAttr->suffixType());
    this->setCurrentValue(newValue);
}

void AttrIntControl::onControlValueChanged(int value, bool cmd)
{
//    if (m_attribute->getValue().toInt() == value) {
//        return;
//    }
//    QObject::disconnect(m_attribute, &IntAttribute::valueChanged, this, &AttrIntControl::onAttrValueChanged);
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    int newValue = NumericAttribute::convertToPixels(value, numericAttr->suffixType());
    m_attribute->setValue(newValue, cmd);
//    QObject::connect(m_attribute, &IntAttribute::valueChanged, this, &AttrIntControl::onAttrValueChanged);
}

void AttrIntControl::onSuffixTypeChanged(NumericAttribute::SuffixType type)
{
    switch(type) {
        case NumericAttribute::ST_PERCENT: {
            this->setSuffix(tr("%"));
            break;
        }
        case NumericAttribute::ST_PX: {
            this->setSuffix(tr("px"));
            break;
        }
        case NumericAttribute::ST_PC: {
            this->setSuffix(tr("pc"));
            break;
        }
        case NumericAttribute::ST_PT: {
            this->setSuffix(tr("pt"));
            break;
        }
        case NumericAttribute::ST_MM: {
            this->setSuffix(tr("mm"));
            break;
        }
        case NumericAttribute::ST_CM: {
            this->setSuffix(tr("cm"));
            break;
        }
        case NumericAttribute::ST_IN: {
            this->setSuffix(tr("in"));
            break;
        }
        default: {
            this->setSuffix(tr(""));
            break;
        }
    }

    int newValue = NumericAttribute::convertFormPixels(m_attribute->getValue().toInt(), type);
    this->setCurrentValue(newValue);
}

void AttrIntControl::onEnableChanged(bool enabled)
{
    qDebug() << "1111111111 enabled" << enabled;
    setEnabled(enabled);
}
