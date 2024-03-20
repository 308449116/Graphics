#ifndef ATTRBOOLCONTROL_H
#define ATTRBOOLCONTROL_H

#include "CustomCombineControl/customswitchcontrol.h"
#include "boolattribute.h"

class AttrBoolControl : public CustomSwitchControl
{
    Q_OBJECT

public:
    AttrBoolControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~AttrBoolControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private:
    BoolAttribute *m_attribute = nullptr;

private slots:
    void onAttrValueChanged(const QVariant& value);
    void onControlValueChanged(bool value, bool cmd = false);
};

#endif
