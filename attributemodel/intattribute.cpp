#include "intattribute.h"
//#include "nodemanager.h"

IntAttribute::IntAttribute(AttributeType type, NodeBase *parentNode)
    : NumericAttribute(type, parentNode)
{
}

IntAttribute::~IntAttribute()
{

}

void IntAttribute::setValueRange(int minValue, int maxValue)
{
    m_MinValue = minValue;
    m_MaxValue = maxValue;
}

void IntAttribute::getValueRange(int& minValue, int& maxValue) const
{
    minValue = m_MinValue;
    maxValue = m_MaxValue;
}
