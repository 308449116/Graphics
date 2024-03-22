#ifndef ATTRINTCONTROL_H
#define ATTRINTCONTROL_H

#include "customintcontrol.h"
#include "intattribute.h"

class AttrIntControl : public CustomIntControl
{
    Q_OBJECT

public:
    AttrIntControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~AttrIntControl();

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
