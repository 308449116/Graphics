#include "groupnode.h"
#include "intattribute.h"
//#include "graphicsobject/graphicstextitem.h"
#include "utils/attribute_constants.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

using namespace Utils::Constants;

GroupNode::GroupNode(GraphicsItem *item)
    :ItemNodeBase(t_Group, item)
{
    initAttribute();
}

GroupNode::~GroupNode()
{

}

void GroupNode::saveToXml(QXmlStreamWriter *xml)
{
    ItemNodeBase::saveToXml(xml);
    xml->writeAttribute(NODENUM, m_nodeNumAttribute->getValue().toString());
}

void GroupNode::loadFromXml(QXmlStreamReader *xml)
{
    ItemNodeBase::loadFromXml(xml);
    int nodeNum = xml->attributes().value(NODENUM).toInt();
    m_nodeNumAttribute->setValue(nodeNum);
}

void GroupNode::initAttribute()
{
    QString attributeGroupString = tr("Group Attribute");
    AttributeGroup *group = this->addAttributeGroup("GroupAttr", attributeGroupString);

    // 节点个数
    m_nodeNumAttribute = new IntAttribute(AttributeBase::SPINBOX_TYPE);
    m_nodeNumAttribute->setEnabled(false);
    m_nodeNumAttribute->setValue(1);
    m_nodeNumAttribute->setValueRange(1, 100);
    m_nodeNumAttribute->setDisplayName(tr("Node Num: "));
    m_nodeNumAttribute->setName(QString::fromUtf8(NODENUM));
    this->addAttribute(group, m_nodeNumAttribute);
}
