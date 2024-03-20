#include "RealAttribute.h"
//#include "Utils.h"
//#include "NodeManager.h"

RealAttribute::RealAttribute(AttributeType type, NodeBase *parentNode)
    : NumericAttribute(type, parentNode)
{
}

RealAttribute::~RealAttribute()
{

}

// 设置/获取 取值范围
void RealAttribute::setValueRange(qreal minValue, qreal maxValue)
{
    m_qMinValue = minValue;
    m_qMaxValue = maxValue;
}

void RealAttribute::getValueRange(qreal& minValue, qreal& maxValue)
{
    minValue = m_qMinValue;
    maxValue = m_qMaxValue;
}
