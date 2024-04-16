#include "itemnodebase.h"
#include "stringattribute.h"
#include "realattribute.h"
#include "graphicsobject/graphicsitem.h"
#include "utils/attribute_constants.h"

#include <QXmlStreamWriter>

using namespace Utils::Constants;

ItemNodeBase::ItemNodeBase(GraphicsItem *item) :
    NodeBase(item), m_item(item)
{
    initNodeBase();
}

ItemNodeBase::ItemNodeBase(NodeType type, GraphicsItem *item) :
    NodeBase(type, item), m_item(item)
{
    initNodeBase();
}

ItemNodeBase::~ItemNodeBase()
{

}

void ItemNodeBase::saveToXml(QXmlStreamWriter *xml)
{
//    xml->writeAttribute(X, m_XPositionAttribute->getValue().toString());
//    xml->writeAttribute(Y, m_YPositionAttribute->getValue().toString());
//    xml->writeAttribute(Z, m_ZPositionAttribute->getValue().toString());
    xml->writeAttribute(WIDTH, m_widthAttribute->getValue().toString());
    xml->writeAttribute(HEIGHT, m_heightAttribute->getValue().toString());
    xml->writeAttribute(ROTATE, m_rotateAttribute->getValue().toString());
    xml->writeAttribute(ITEMNAME, m_nameAttribute->getValue().toString());
    xml->writeAttribute(ID, m_IDAttribute->getValue().toString());
}

void ItemNodeBase::loadFromXml(QXmlStreamReader *xml)
{
//    qreal x = xml->attributes().value(X).toDouble();
//    qreal y = xml->attributes().value(Y).toDouble();
//    qreal z = xml->attributes().value(Z).toDouble();
    qreal width = xml->attributes().value(WIDTH).toDouble();
    qreal height = xml->attributes().value(HEIGHT).toDouble();
    qreal rotate = xml->attributes().value(ROTATE).toDouble();
    QString itemName = xml->attributes().value(ITEMNAME).toString();
    QString id = xml->attributes().value(ID).toString();

    qDebug() << "======== width:" << width
             << "height:" << height << "  rotate:" << rotate
             << "  itemName:" << itemName
             << "  id:" << id;

    m_rotateAttribute->setValue(rotate);
    m_widthAttribute->setValue(width);
    m_heightAttribute->setValue(height);
    m_nameAttribute->setValue(itemName);
    m_IDAttribute->setValue(id);
//    m_XPositionAttribute->setValue(x);
//    m_YPositionAttribute->setValue(y);
//    m_ZPositionAttribute->setValue(z);
}

//void ItemNodeBase::readBaseAttributes(QXmlStreamReader *xml)
//{

//}

//void ItemNodeBase::writeBaseAttributes(QXmlStreamWriter *xml)
//{

//}

void ItemNodeBase::initNodeBase()
{
    if (m_item == nullptr) {
        return;
    }

    // 添加属性组
    QString attributeGroupString = tr("Base Attribute");
    AttributeGroup *group = this->addAttributeGroup("BaseAttr", attributeGroupString);

    // X坐标
    m_XPositionAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_XPositionAttribute->setDisplayName(tr("X Position: "));
    m_XPositionAttribute->setName(QString::fromUtf8(X));
    m_XPositionAttribute->setValueRange(0, 5000);
    this->addAttribute(group, m_XPositionAttribute);

    // Y坐标
    m_YPositionAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_YPositionAttribute->setDisplayName(tr("Y Position: "));
    m_YPositionAttribute->setName(QString::fromUtf8(Y));
    m_YPositionAttribute->setValueRange(0, 5000);
    this->addAttribute(group, m_YPositionAttribute);

    // Z坐标
//    m_ZPositionAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
//    m_ZPositionAttribute->setDisplayName(tr("Z Position: "));
//    m_ZPositionAttribute->setName(QString::fromUtf8(Z));
//    m_ZPositionAttribute->setValueRange(0, 10);
//    this->addAttribute(group, m_ZPositionAttribute);

    // 宽度
    m_widthAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_widthAttribute->setDisplayName(tr("Width: "));
    m_widthAttribute->setName(QString::fromUtf8(WIDTH));
    m_widthAttribute->setValueRange(10, 5000);
    this->addAttribute(group, m_widthAttribute);

    // 高度
    m_heightAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_heightAttribute->setDisplayName(tr("Height: "));
    m_heightAttribute->setName(QString::fromUtf8(HEIGHT));
    m_heightAttribute->setValueRange(10, 5000);
    this->addAttribute(group, m_heightAttribute);

    // 旋转
    m_rotateAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_rotateAttribute->setDisplayName(tr("Rotate Angle: "));
    m_rotateAttribute->setName(QString::fromUtf8(ROTATE));
    m_rotateAttribute->setValueRange(0, 360);
    m_rotateAttribute->setValue(0);
    this->addAttribute(group, m_rotateAttribute);

    // 名字
    m_nameAttribute = new StringAttribute(AttributeBase::LINEEDIT_TYPE);
    m_nameAttribute->setDisplayName(tr("Name: "));
    m_nameAttribute->setName(QString::fromUtf8(ITEMNAME));
    m_nameAttribute->setValue("");
    this->addAttribute(group, m_nameAttribute);

    // id
    m_IDAttribute = new StringAttribute(AttributeBase::LINEEDIT_TYPE);
    m_IDAttribute->setEnabled(false);
    m_IDAttribute->setDisplayName(tr("ID: "));
    m_IDAttribute->setName(QString::fromUtf8(ID));
    m_IDAttribute->setValue("");
    this->addAttribute(group, m_IDAttribute);

    // 连接信号和槽
    QObject::connect(m_XPositionAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onXPositionAttributeValueChanged);
    QObject::connect(m_YPositionAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onYPositionAttributeValueChanged);
//    QObject::connect(m_ZPositionAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onZPositionAttributeValueChanged);
    QObject::connect(m_widthAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onWidthAttributeValueChanged);
    QObject::connect(m_heightAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onHeightAttributeValueChanged);
    QObject::connect(m_rotateAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onRotateAttributeValueChanged);
    QObject::connect(m_nameAttribute, &StringAttribute::valueChanged, m_item, &GraphicsItem::onNameAttributeValueChanged);
    QObject::connect(m_IDAttribute, &StringAttribute::valueChanged, m_item, &GraphicsItem::onIDAttributeValueChanged);

    //测试使用
//    QObject::connect(m_ZPositionAttribute, &RealAttribute::valueChanged, this, &ItemNodeBase::onXYSuffixChanged);
}

void ItemNodeBase::onXYSuffixChanged(const QVariant& value)
{
    m_XPositionAttribute->setSuffixType((NumericAttribute::SuffixType)value.toInt());
    m_YPositionAttribute->setSuffixType((NumericAttribute::SuffixType)value.toInt());
}
