#ifndef ATTRBOOLCONTROL_H
#define ATTRBOOLCONTROL_H

#include "custom_ui/customcontrols/customcombinecontrol/customswitchcontrol.h"
#include "attributemodel/boolattribute.h"

class AttrBoolControl : public CustomSwitchControl
{
    Q_OBJECT

public:
    AttrBoolControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~AttrBoolControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private slots:
    void onAttrValueChanged(const QVariant& value);
    void onControlValueChanged(bool value, bool cmd = false);

private:
    BoolAttribute *m_attribute = nullptr;
};

#endif
