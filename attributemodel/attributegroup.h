#ifndef ATTRIBUTEGROUP_H
#define ATTRIBUTEGROUP_H

#include <QObject>

class AttributeBase;
class NodeBase;
class AttributeGroup : public QObject
{
    Q_OBJECT

public:
    AttributeGroup(QObject *parent = nullptr);
    ~AttributeGroup();

    // 添加删除属性
    void addAttribute(AttributeBase *attribute);

    // 删除属性
    void deleteAttribute(AttributeBase *attribute);

    // 获取全部属性
    const QList<AttributeBase*> &getAttributes();
    AttributeBase *getAttribute(const QString& name) const;

    // 设置父节点
    void setParentNode(NodeBase *node);
    NodeBase *getParentNode() const;

    // 设置/获取属性组的名称
    void setName(const QString& name);
    QString getName() const;

    // 设置/获取属性组的显示名称
    void setDisplayName(const QString& name);
    QString getDisplayName() const;

private:
    NodeBase *m_parentNode = nullptr;
    QList<AttributeBase*> m_attributes;
    QString m_groupName;
    QString m_displayName;
};

#endif
