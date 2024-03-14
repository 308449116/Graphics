#ifndef INTATTRIBUTE_H
#define INTATTRIBUTE_H

#include "AttributeBase.h"

class IntAttribute : public AttributeBase
{
    Q_OBJECT

public:
    IntAttribute(AttributeType type, NodeBase* parentNode = nullptr);
    ~IntAttribute();

    // 设置/获取 取值范围
    void setValueRange(int minValue, int maxValue);
    void getValueRange(int& minValue, int& maxValue);

private:
    int m_MinValue = 0;
    int m_MaxValue = 100;
};

#endif
