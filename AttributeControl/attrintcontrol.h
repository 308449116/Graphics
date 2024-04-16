#ifndef ATTRINTCONTROL_H
#define ATTRINTCONTROL_H

#include "custom_ui/customcontrols/customcombinecontrol/customintcontrol.h"
#include "attributemodel/intattribute.h"

class AttrIntControl : public CustomIntControl
{
    Q_OBJECT

public:
    AttrIntControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~AttrIntControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private slots:
    void onAttrValueChanged(const QVariant& value);
    void onControlValueChanged(int value, bool cmd = false);
    void onSuffixTypeChanged(NumericAttribute::SuffixType type);
    void onEnableChanged(bool enabled);

private:
    IntAttribute *m_attribute = nullptr;
};

#endif
