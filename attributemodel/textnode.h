#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "itemnodebase.h"

class StringAttribute;
class IntAttribute;
class TextNode : public ItemNodeBase
{
public:
    TextNode(GraphicsItem *item);
    ~TextNode();

   void saveToXml(QXmlStreamWriter *xml) override;

   void loadFromXml(QXmlStreamReader *xml) override;

private:
    void initAttribute();

    StringAttribute *m_textValueAttribute = nullptr;
    IntAttribute *m_fontSizeAttribute = nullptr;
//    StringAttribute *m_fontFamilyAttr = nullptr;
};

#endif
