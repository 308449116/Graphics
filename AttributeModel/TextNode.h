#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "NodeBase.h"

class StringAttribute;
class IntAttribute;
class TextNode : public NodeBase
{
public:
    TextNode(GraphicsItem *item);
    ~TextNode();

private:
    void initAttribute();

    StringAttribute* m_pTextValueAttribute = nullptr;
    IntAttribute* m_pFontSizeAttribute = nullptr;
//    StringAttribute* m_pFontFamilyAttr = nullptr;
};

#endif
