#ifndef UIATTRFLOATCONTROL_H
#define UIATTRFLOATCONTROL_H

#include "CustomCombineControl/UICustomDoubleControl.h"
#include "RealAttribute.h"

class UIAttrFloatControl : public UICustomDoubleControl
{
    Q_OBJECT

public:
    UIAttrFloatControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~UIAttrFloatControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private:
    RealAttribute *m_attribute = nullptr;

private slots:
    void onValueChanged(const QVariant& value);
    void onControlValueChanged(qreal value, bool cmd = false);
    void onSuffixTypeChanged(NumericAttribute::SuffixType type);
};

#endif
