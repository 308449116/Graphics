#ifndef BOOLATTRIBTE_H
#define BOOLATTRIBTE_H

#include "attributebase.h"

class BoolAttribute : public AttributeBase
{
    Q_OBJECT
public:
    BoolAttribute(AttributeType type, NodeBase *parentNode = nullptr);
    ~BoolAttribute();
};

#endif
