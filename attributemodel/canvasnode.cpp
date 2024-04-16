#include "canvasnode.h"
#include "realattribute.h"
#include "scenegraphics.h"
#include "utils/attribute_constants.h"

#include <QXmlStreamWriter>

using namespace Utils::Constants;

CanvasNode::CanvasNode(SceneGraphics *scene) :
    NodeBase(t_Canvas, scene), m_scene(scene)
{
    initAttribute();
}

CanvasNode::~CanvasNode()
{

}

void CanvasNode::saveToXml(QXmlStreamWriter *xml)
{
    xml->writeAttribute(WIDTH, m_widthAttribute->getValue().toString());
    xml->writeAttribute(HEIGHT, m_heightAttribute->getValue().toString());
}

void CanvasNode::loadFromXml(QXmlStreamReader *xml)
{
    qreal width = xml->attributes().value(WIDTH).toDouble();
    qreal height = xml->attributes().value(HEIGHT).toDouble();

    m_widthAttribute->setValue(width);
    m_heightAttribute->setValue(height);
}

void CanvasNode::initAttribute()
{
    // 添加属性组
    QString attributeGroupString = tr("Canvas Attribute");
    AttributeGroup *group = this->addAttributeGroup("CanvasAttr", attributeGroupString);

    // 宽度
    m_widthAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_widthAttribute->setDisplayName(tr("width: "));
    m_widthAttribute->setName(QString::fromUtf8(WIDTH));
    m_widthAttribute->setValueRange(10, 5000);
    this->addAttribute(group, m_widthAttribute);

    // 高度
    m_heightAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_heightAttribute->setDisplayName(tr("height: "));
    m_heightAttribute->setName(QString::fromUtf8(HEIGHT));
    m_heightAttribute->setValueRange(10, 5000);
    this->addAttribute(group, m_heightAttribute);

    QObject::connect(m_widthAttribute, &RealAttribute::valueChanged, m_scene, &SceneGraphics::onWidthAttributeValueChanged);
    QObject::connect(m_heightAttribute, &RealAttribute::valueChanged, m_scene, &SceneGraphics::onHeightAttributeValueChanged);
}

