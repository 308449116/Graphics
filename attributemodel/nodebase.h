#ifndef NODEBASE_H
#define NODEBASE_H

#include "attributebase.h"
#include "attributegroup.h"

class GraphicsItem;
class AttributeBase;
class RealAttribute;
class IntAttribute;
class StringAttribute;
class QXmlStreamWriter;
class QXmlStreamReader;
class NodeBase : public QObject
{
    Q_OBJECT

public:
    enum NodeType
    {
        t_textNode,
        t_RectNode,
        t_Elleipse,
        t_Canvas,
        t_Group,
        t_End
    };

public:
    explicit NodeBase(QObject *parent = nullptr);
    explicit NodeBase(NodeType type, QObject *parent = nullptr);
    ~NodeBase();

    // 设置/获取节点类型
    void setNodeType(int type);
    virtual int getNodeType() const;

    // 设置节点名字
    void setNodeName(const QString& nodeName);
    QString getNodeName() const;

    // 获取属性组
    const QList<AttributeGroup*> &getAllAttributeGroups();

    // 添加属性组
    void addAttributeGroup(AttributeGroup *group);
    AttributeGroup *addAttributeGroup(const QString& name);
    AttributeGroup *addAttributeGroup(const QString& name, const QString& displayName);

    // 删除属性组
    void deleteAttributeGroup(AttributeGroup *group);
    void deleteAttributeGroup(const QString& name);

    // 添加属性
    bool addAttribute(AttributeGroup *group, AttributeBase *attribute);
    bool addAttribute(const QString& groupName, AttributeBase *attribute);
    bool addAttribute(const QString& groupName, const QString& name, AttributeBase::AttributeType type);

    // 删除属性
    bool deleteAttribute(AttributeBase *attribute);
    bool deleteAttribute(const QString& name);

    // 查找属性
    AttributeBase *getAttribute(const QString& attrName) const;

    virtual void saveToXml(QXmlStreamWriter *xml) = 0;

    virtual void loadFromXml(QXmlStreamReader *xml) = 0;

//    void readBaseAttributes(QXmlStreamReader *xml);
//    void writeBaseAttributes(QXmlStreamWriter *xml);

private:
    QList<AttributeGroup*> m_groupList;
    int m_nodeType;
    QString m_name;     // 节点名字
};

#endif
