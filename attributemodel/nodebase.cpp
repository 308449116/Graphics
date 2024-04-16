#include "nodebase.h"
#include "attributegroup.h"

NodeBase::NodeBase(NodeType type, QObject *item)
    :QObject(item)
    ,m_nodeType(type)
{
}

NodeBase::NodeBase(QObject *item)
    :QObject (item)
{
}

NodeBase::~NodeBase()
{

}

// 设置/获取节点类型
void NodeBase::setNodeType(int type)
{
    m_nodeType = type;
}

int NodeBase::getNodeType() const
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
    for (auto goup : m_groupList) {
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
    for (auto item : m_groupList) {
        if (AttributeBase *attribute = item->getAttribute(name)) {
            deleteAttribute(attribute);
            return true;
        }
    }

    return false;
}


// 查找属性
AttributeBase *NodeBase::getAttribute(const QString& attrName) const
{
    for (auto item : m_groupList) {
        if (AttributeBase *attribute = item->getAttribute(attrName)) {
            return attribute;
        }
    }
    
    return nullptr;
}

// 设置节点名字
void NodeBase::setNodeName(const QString& nodeName)
{
    m_name = nodeName;
}

QString NodeBase::getNodeName() const
{
    return m_name;
}

const QList<AttributeGroup*> &NodeBase::getAllAttributeGroups()
{
    return m_groupList;
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
