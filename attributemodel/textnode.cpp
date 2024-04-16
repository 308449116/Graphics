#include "textnode.h"
#include "intattribute.h"
#include "stringattribute.h"
#include "graphicsobject/graphicstextitem.h"
#include "utils/attribute_constants.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

using namespace Utils::Constants;

TextNode::TextNode(GraphicsItem *item)
    :ItemNodeBase(t_textNode, item)
{
    initAttribute();
}

TextNode::~TextNode()
{
    
}

void TextNode::saveToXml(QXmlStreamWriter *xml)
{
    ItemNodeBase::saveToXml(xml);
    xml->writeAttribute(FONTSIZE, m_fontSizeAttribute->getValue().toString());
    xml->writeCharacters(m_textValueAttribute->getValue().toString());
}

void TextNode::loadFromXml(QXmlStreamReader *xml)
{
    ItemNodeBase::loadFromXml(xml);
    int fontSize = xml->attributes().value(FONTSIZE).toInt();
    QString text = xml->readElementText();

    m_fontSizeAttribute->setValue(fontSize);
    m_textValueAttribute->setValue(text);
}

void TextNode::initAttribute()
{
    if (m_item == nullptr) {
        return;
    }

    QString attributeGroupString = tr("Text Attribute");
    AttributeGroup *group = this->addAttributeGroup("TextAttr", attributeGroupString);

    // 本文内容
    m_textValueAttribute = new StringAttribute(AttributeBase::LINEEDIT_TYPE);
    m_textValueAttribute->setValue("test");
    m_textValueAttribute->setDisplayName(tr("Text Content: "));
    m_textValueAttribute->setName(QString::fromUtf8(TEXTCONTENT));
    m_textValueAttribute->setShowButton(false);
    this->addAttribute(group, m_textValueAttribute);

    // 字体大小
    m_fontSizeAttribute = new IntAttribute(AttributeBase::SPINBOX_TYPE);
    m_fontSizeAttribute->setValue(100);
    m_fontSizeAttribute->setValueRange(1, 200);
    m_fontSizeAttribute->setDisplayName(tr("Font Size: "));
    m_fontSizeAttribute->setName(QString::fromUtf8(FONTSIZE));
    this->addAttribute(group, m_fontSizeAttribute);

    GraphicsTextItem *textItem = dynamic_cast<GraphicsTextItem *>(m_item);
    QObject::connect(m_fontSizeAttribute, &IntAttribute::valueChanged, textItem, &GraphicsTextItem::onFontSizeValueChanged);
    QObject::connect(m_textValueAttribute, &StringAttribute::valueChanged, textItem, &GraphicsTextItem::onTextValueChanged);
}
