#ifndef REALATTRIBUTE_H
#define REALATTRIBUTE_H

#include "numericattribute.h"

class NodeBase;
class RealAttribute : public NumericAttribute
{
    Q_OBJECT

public:
    RealAttribute(AttributeType type, NodeBase *parentNode = nullptr);
    ~RealAttribute();

    // 设置/获取 取值范围
    void setValueRange(qreal minValue, qreal maxValue);
    void getValueRange(qreal& minValue, qreal& maxValue);

private:
    qreal m_qMinValue = 0;
    qreal m_qMaxValue = 100;
};

#endif
