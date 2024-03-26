#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "nodebase.h"

constexpr const char *TEXT = "text";
constexpr const char *FONTSIZE = "fontSize";

class StringAttribute;
class IntAttribute;
class TextNode : public NodeBase
{
public:
    TextNode(GraphicsItem *item);
    ~TextNode();

private:
    void initAttribute();

    StringAttribute *m_pTextValueAttribute = nullptr;
    IntAttribute *m_pFontSizeAttribute = nullptr;
//    StringAttribute *m_pFontFamilyAttr = nullptr;
};

#endif
