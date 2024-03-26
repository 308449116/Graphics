#include "boolattribute.h"
//#include "nodemanager.h"

BoolAttribute::BoolAttribute(AttributeType type, NodeBase *parentNode)
    :AttributeBase(type, parentNode)
{
    m_value = true;
}

BoolAttribute::~BoolAttribute()
{

}
