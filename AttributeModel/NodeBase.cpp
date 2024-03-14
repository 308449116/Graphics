#include "NodeBase.h"
#include "IntAttribute.h"
#include "RealAttribute.h"
#include "AttributeGroup.h"
#include "graphicsitem.h"
#include "common.h"

NodeBase::NodeBase(GraphicsItem *item, NodeType type)
    :QObject(item)
    ,m_item(item)
    ,m_nodeType(type)
{
    initNodeBase();
}

NodeBase::NodeBase(GraphicsItem *item)
    :QObject (item)
    ,m_item(item)
{
    initNodeBase();
}

NodeBase::~NodeBase()
{

}

// 设置/获取节点类型
void NodeBase::setNodeType(int type)
{
    m_nodeType = type;
}

int NodeBase::getNodeType()
{
    return m_nodeType;
}

// 添加属性
bool NodeBase::addAttribute(AttributeGroup *group, AttributeBase *attribute)
{
    if (group == nullptr || attribute == nullptr)
        return false;

    group->addAttribute(attribute);
    attribute->setParentNode(this);
    return true;
}

bool NodeBase::addAttribute(const QString& groupName, AttributeBase *attribute)
{
    if (attribute == nullptr)
        return false;

    AttributeGroup *attributeGroup = nullptr;
    foreach(auto goup, m_groupList) {
        if (groupName == goup->getName()) {
            attributeGroup = goup;
            break;
        }
    }

    if (attributeGroup == nullptr)
        return false;

    return addAttribute(attributeGroup, attribute);
}

bool NodeBase::addAttribute(const QString& groupName, const QString& name, AttributeBase::AttributeType type)
{
    AttributeBase *attribute = AttributeBase::createAttribute(name, type);
    addAttribute(groupName, attribute);
    return true;
}

// 删除属性
bool NodeBase::deleteAttribute(AttributeBase *attribute)
{
    auto group = attribute->getParentGroup();
    if (group == nullptr)
        return false;

    group->deleteAttribute(attribute);
    return true;
}

bool NodeBase::deleteAttribute(const QString& name)
{
    foreach (auto item, m_groupList) {
        if (AttributeBase *attribute = item->getAttribute(name)) {
            deleteAttribute(attribute);
            return true;
        }
    }

    return false;
}


// 查找属性
AttributeBase *NodeBase::getAttribute(const QString& attrName)
{
    foreach (auto item, m_groupList) {
        if (AttributeBase *attribute = item->getAttribute(attrName)) {
            return attribute;
        }
    }

    return nullptr;
}

void NodeBase::initNodeBase()
{
    if (m_item == nullptr) {
        return;
    }

    // 添加属性组
    QString attributeGroupString = tr("Base Attribute");
    AttributeGroup *group = this->addAttributeGroup("BaseAttr", attributeGroupString);

    // X坐标
    m_pXPositionAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_pXPositionAttribute->setDisplayName(tr("X Position: "));
    m_pXPositionAttribute->setName(X);
    m_pXPositionAttribute->setValueRange(0, 5000);
    this->addAttribute(group, m_pXPositionAttribute);

    // Y坐标
    m_pYPositionAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_pYPositionAttribute->setDisplayName(tr("Y Position: "));
    m_pYPositionAttribute->setName(Y);
    m_pYPositionAttribute->setValueRange(0, 5000);
    this->addAttribute(group, m_pYPositionAttribute);

    // Z坐标
    m_pZPositionAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_pZPositionAttribute->setDisplayName(tr("Z Position: "));
    m_pZPositionAttribute->setName(Z);
    m_pZPositionAttribute->setValueRange(0, 10);
    this->addAttribute(group, m_pZPositionAttribute);

    // 宽度
    m_pWidthAttribute = new IntAttribute(AttributeBase::SPINBOX_TYPE);
    m_pWidthAttribute->setDisplayName(tr("width: "));
    m_pWidthAttribute->setName(WIDTH);
    m_pWidthAttribute->setValueRange(10, 5000);
    this->addAttribute(group, m_pWidthAttribute);

    // 高度
    m_pHeightAttribute = new IntAttribute(AttributeBase::SPINBOX_TYPE);
    m_pHeightAttribute->setDisplayName(tr("height: "));
    m_pHeightAttribute->setName(HEIGHT);
    m_pHeightAttribute->setValueRange(10, 5000);
    this->addAttribute(group, m_pHeightAttribute);

    // 旋转
    m_pRotateAttribute = new RealAttribute(AttributeBase::DOUBLESPINBOX_TYPE);
    m_pRotateAttribute->setDisplayName(tr("Rotate Angle: "));
    m_pRotateAttribute->setName(ROTATE);
    m_pRotateAttribute->setValueRange(0, 360);
    m_pRotateAttribute->setValue(0);
    this->addAttribute(group, m_pRotateAttribute);

    // 连接信号和槽
    QObject::connect(m_pXPositionAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onXPositionAttributeValueChanged);
    QObject::connect(m_pYPositionAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onYPositionAttributeValueChanged);
    QObject::connect(m_pZPositionAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onZPositionAttributeValueChanged);
    QObject::connect(m_pWidthAttribute, &IntAttribute::valueChanged, m_item, &GraphicsItem::onWidthAttributeValueChanged);
    QObject::connect(m_pHeightAttribute, &IntAttribute::valueChanged, m_item, &GraphicsItem::onHeightAttributeValueChanged);
    QObject::connect(m_pRotateAttribute, &RealAttribute::valueChanged, m_item, &GraphicsItem::onRotateAttributeValueChanged);
}

// 设置节点名字
void NodeBase::setNodeName(const QString& nodeName)
{
    m_name = nodeName;
}

QString NodeBase::getNodeName()
{
    return m_name;
}

void NodeBase::getAllAttributeGroups(QList<AttributeGroup*>& groups)
{
    groups = m_groupList;
}

void NodeBase::addAttributeGroup(AttributeGroup *group)
{
    if (group == nullptr)
        return;

    group->setParentNode(this);
    m_groupList.append(group);
}

AttributeGroup *NodeBase::addAttributeGroup(const QString& name)
{
    AttributeGroup *group = new AttributeGroup;
    group->setName(name);
    group->setDisplayName(name);
    addAttributeGroup(group);

    return group;
}

AttributeGroup *NodeBase::addAttributeGroup(const QString& name, const QString& displayName)
{
    AttributeGroup *group = new AttributeGroup;
    group->setName(name);
    group->setDisplayName(displayName);
    addAttributeGroup(group);

    return group;
}

// 删除属性组
void NodeBase::deleteAttributeGroup(AttributeGroup *group)
{
    for (auto iter = m_groupList.constBegin(); iter != m_groupList.constEnd(); ++iter) {
        if (*iter == group) {
            m_groupList.erase(iter);
            group->deleteLater();
            break;
        }
    }
}

void NodeBase::deleteAttributeGroup(const QString& name)
{
    for (auto iter = m_groupList.constBegin(); iter != m_groupList.constEnd(); ++iter) {
        if ((*iter)->getName() == name) {
            m_groupList.erase(iter);
            (*iter)->deleteLater();
            break;
        }
    }
}
