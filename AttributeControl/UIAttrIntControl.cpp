#include "UIAttrIntControl.h"
#include "numericattribute.h"

UIAttrIntControl::UIAttrIntControl(AttributeBase *attribute, QWidget *parent)
    :UICustomIntControl(parent)
{
    setAttribute(attribute);

    QObject::connect(m_attribute, &IntAttribute::valueChanged, this, &UIAttrIntControl::onAttrValueChanged);
    QObject::connect(this, &UIAttrIntControl::valueChanged, this, &UIAttrIntControl::onControlValueChanged);

    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    QObject::connect(numericAttr, &NumericAttribute::suffixTypeChanged, this, &UIAttrIntControl::onSuffixTypeChanged);
}

UIAttrIntControl::~UIAttrIntControl()
{

}

// 设置属性
void UIAttrIntControl::setAttribute(AttributeBase *attribute)
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
}

void UIAttrIntControl::onAttrValueChanged(const QVariant& value)
{
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    int newValue = NumericAttribute::convertFormPixels(value.toInt(), numericAttr->suffixType());
    this->setCurrentValue(newValue);
}

void UIAttrIntControl::onControlValueChanged(int value, bool cmd)
{
//    if (m_attribute->getValue().toInt() == value) {
//        return;
//    }
//    QObject::disconnect(m_attribute, &IntAttribute::valueChanged, this, &UIAttrIntControl::onAttrValueChanged);
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    int newValue = NumericAttribute::convertToPixels(value, numericAttr->suffixType());
    m_attribute->setValue(newValue, cmd);
//    QObject::connect(m_attribute, &IntAttribute::valueChanged, this, &UIAttrIntControl::onAttrValueChanged);
}

void UIAttrIntControl::onSuffixTypeChanged(NumericAttribute::SuffixType type)
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

    int newValue = NumericAttribute::convertFormPixels(this->getCurrentValue(), type);
    this->setCurrentValue(newValue);
}
