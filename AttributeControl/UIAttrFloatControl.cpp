#include "UIAttrFloatControl.h"
#include <QDebug>

UIAttrFloatControl::UIAttrFloatControl(AttributeBase *attribute, QWidget *parent)
    :UICustomDoubleControl(parent)
{
    setAttribute(attribute);

    QObject::connect(m_attribute, &RealAttribute::valueChanged, this, &UIAttrFloatControl::onValueChanged);
    QObject::connect(this, &UIAttrFloatControl::valueChanged, this, &UIAttrFloatControl::onControlValueChanged);

    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    QObject::connect(numericAttr, &NumericAttribute::suffixTypeChanged, this, &UIAttrFloatControl::onSuffixTypeChanged);
}

UIAttrFloatControl::~UIAttrFloatControl()
{

}

void UIAttrFloatControl::setAttribute(AttributeBase *attribute)
{
    if (attribute == nullptr || attribute->Type() != AttributeBase::DOUBLESPINBOX_TYPE) {
        return;
    }

    m_attribute = qobject_cast<RealAttribute*>(attribute);
    if (m_attribute == nullptr) {
        return;
    }

    // 设置范围
    qreal startValue, endValue;
    m_attribute->getValueRange(startValue, endValue);
    this->setRangeValue(startValue, endValue);

    // 设置值
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    onSuffixTypeChanged(numericAttr->suffixType());
//    setSuffixByType(numericAttr->suffixType());
//    int newValue = NumericAttribute::convertFormPixels(m_attribute->getValue().toDouble(), numericAttr->suffixType());
//    this->setCurrentValue(newValue);

//    this->setCurrentValue(m_attribute->getValue().toDouble());
    this->setTagText(m_attribute->getDisplayName());
}

void UIAttrFloatControl::onValueChanged(const QVariant& value)
{
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    qreal newValue = NumericAttribute::convertFormPixels(value.toInt(), numericAttr->suffixType());
    this->setCurrentValue(newValue);
}

void UIAttrFloatControl::onControlValueChanged(qreal value, bool cmd)
{
//    if (m_attribute->getValue().toDouble() == value) {
//        return;
//    }

//    QObject::disconnect(m_attribute, &RealAttribute::valueChanged, this, &UIAttrFloatControl::onValueChanged);
    NumericAttribute *numericAttr = dynamic_cast<NumericAttribute *>(m_attribute);
    qreal newValue = NumericAttribute::convertToPixels(value, numericAttr->suffixType());
    m_attribute->setValue(newValue, cmd);
//    QObject::connect(m_attribute, &RealAttribute::valueChanged, this, &UIAttrFloatControl::onValueChanged);
}

void UIAttrFloatControl::onSuffixTypeChanged(NumericAttribute::SuffixType type)
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

    qreal newValue = NumericAttribute::convertFormPixels(m_attribute->getValue().toDouble(), type);
    this->setCurrentValue(newValue);
}
