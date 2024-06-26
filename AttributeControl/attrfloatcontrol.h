#ifndef ATTRFLOATCONTROL_H
#define ATTRFLOATCONTROL_H

#include "custom_ui/customcontrols/customcombinecontrol/customdoublecontrol.h"
#include "attributemodel/realattribute.h"

class AttrFloatControl : public CustomDoubleControl
{
    Q_OBJECT

public:
    AttrFloatControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~AttrFloatControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private slots:
    void onValueChanged(const QVariant& value);
    void onControlValueChanged(qreal value, bool cmd = false);
    void onSuffixTypeChanged(NumericAttribute::SuffixType type);

private:
    RealAttribute *m_attribute = nullptr;
};

#endif
