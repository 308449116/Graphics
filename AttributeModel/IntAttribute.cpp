#include "IntAttribute.h"
//#include "NodeManager.h"

IntAttribute::IntAttribute(AttributeType type, NodeBase* parentNode)
    :AttributeBase(type, parentNode)
{
    m_value = 0;
}

IntAttribute::~IntAttribute()
{

}

// 设置/获取 取值范围
void IntAttribute::setValueRange(int minValue, int maxValue)
{
    m_MinValue = minValue;
    m_MaxValue = maxValue;
}

void IntAttribute::getValueRange(int& minValue, int& maxValue)
{
    minValue = m_MinValue;
    maxValue = m_MaxValue;
}
