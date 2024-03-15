#ifndef UIATTRBOOLCONTROL_H
#define UIATTRBOOLCONTROL_H

#include "CustomCombineControl/UICustomSwitchControl.h"
#include "BoolAttribute.h"

class  UIAttrBoolControl : public UICustomSwitchControl
{
    Q_OBJECT

public:
    UIAttrBoolControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~UIAttrBoolControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private:
    BoolAttribute *m_attribute = nullptr;

private slots:
    void onAttrValueChanged(const QVariant& value);
    void onControlValueChanged(bool value, bool cmd = false);
};

#endif
