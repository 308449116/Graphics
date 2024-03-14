#include "TextNode.h"
#include "IntAttribute.h"
#include "StringAttribute.h"
#include "graphicstextitem.h"
#include "common.h"

TextNode::TextNode(GraphicsItem *item)
    :NodeBase(item, t_textNode)
{
    initAttribute();
}

TextNode::~TextNode()
{

}

void TextNode::initAttribute()
{
    if (m_item == nullptr) {
        return;
    }

    QString groupName = tr("Text Attribute");
    this->addAttributeGroup(groupName);

    // 本文内容
    m_pTextValueAttribute = new StringAttribute(AttributeBase::LINEEDIT_TYPE);
    m_pTextValueAttribute->setValue("test");
    m_pTextValueAttribute->setDisplayName(tr("Text: "));
    m_pTextValueAttribute->setName(TEXT);
    m_pTextValueAttribute->setShowButton(false);
    this->addAttribute(groupName, m_pTextValueAttribute);

    // 字体大小
    m_pFontSizeAttribute = new IntAttribute(AttributeBase::SPINBOX_TYPE);
    m_pFontSizeAttribute->setValue(100);
    m_pFontSizeAttribute->setValueRange(1, 200);
    m_pFontSizeAttribute->setDisplayName(tr("Font Size: "));
    m_pFontSizeAttribute->setName(FONTSIZE);
    this->addAttribute(groupName, m_pFontSizeAttribute);

    GraphicsTextItem *textItem = dynamic_cast<GraphicsTextItem *>(m_item);
    QObject::connect(m_pFontSizeAttribute, &IntAttribute::valueChanged, textItem, &GraphicsTextItem::onFontSizeValueChanged);
    QObject::connect(m_pTextValueAttribute, &StringAttribute::valueChanged, textItem, &GraphicsTextItem::onTextValueChanged);
}
