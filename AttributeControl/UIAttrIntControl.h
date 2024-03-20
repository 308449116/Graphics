#ifndef UIATTRINTCONTROL_H
#define UIATTRINTCONTROL_H

#include "CustomCombineControl/UICustomIntControl.h"
#include "IntAttribute.h"

class UIAttrIntControl : public UICustomIntControl
{
    Q_OBJECT

public:
    UIAttrIntControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~UIAttrIntControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private:
    IntAttribute *m_attribute = nullptr;

private slots:
    void onAttrValueChanged(const QVariant& value);
    void onControlValueChanged(int value, bool cmd = false);
    void onSuffixTypeChanged(NumericAttribute::SuffixType type);
};

#endif
