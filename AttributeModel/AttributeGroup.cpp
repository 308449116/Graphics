#include "attributegroup.h"
#include "attributebase.h"
#include "nodebase.h"

AttributeGroup::AttributeGroup(QObject *parent)
    :QObject(parent)
{

}

AttributeGroup::~AttributeGroup()
{

}

// 添加删除属性
void AttributeGroup::addAttribute(AttributeBase *attribute)
{
    if (attribute == nullptr)
        return;

    m_attributes.push_back(attribute);
    attribute->setParentGroup(this);
}

// 删除属性
void AttributeGroup::deleteAttribute(AttributeBase *attribute)
{
    for (auto iter = m_attributes.constBegin(); iter != m_attributes.constEnd(); ++iter)
    {
        if (*iter == attribute)
        {
            m_attributes.erase(iter);
            attribute->deleteLater();
            break;
        }
    }
}

const QList<AttributeBase*> &AttributeGroup::getAttributes()
{
    return  m_attributes;
}

AttributeBase *AttributeGroup::getAttribute(const QString& name) const
{
    for (auto item : m_attributes) {
        if (item->getName() == name) {
            return item;
        }
    }

    return nullptr;
}

// 设置父节点
void AttributeGroup::setParentNode(NodeBase *node)
{
    m_pParentNode = node;
    this->setParent(node);
}

NodeBase *AttributeGroup::getParentNode() const
{
    return m_pParentNode;
}

// 设置/获取属性组的名称
void AttributeGroup::setName(const QString& name)
{
    m_groupName = name;
}

QString AttributeGroup::getName() const
{
    return m_groupName;
}

void AttributeGroup::setDisplayName(const QString& name)
{
    m_displayName = name;
}

QString AttributeGroup::getDisplayName() const
{
    return m_displayName;
}
