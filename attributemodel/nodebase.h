#ifndef NODEBASE_H
#define NODEBASE_H

#include "attributebase.h"
#include "attributegroup.h"

static constexpr const char *X = "xPt";
static constexpr const char *Y = "yPt";
static constexpr const char *Z = "zPt";
static constexpr const char *WIDTH = "width";
static constexpr const char *HEIGHT = "height";
static constexpr const char *ROTATE = "rotate";

class GraphicsItem;
class AttributeBase;
class RealAttribute;
class IntAttribute;
class NodeBase : public QObject
{
    Q_OBJECT

public:
    enum NodeType
    {
        t_textNode,
        t_RectNode,
        t_Elleipse,
        t_Arrow,
        t_FreeDraw,

        t_User,         // 自定义节点类型
        t_End
    };

public:
    explicit NodeBase(GraphicsItem *item);
    explicit NodeBase(GraphicsItem *item, NodeType type);
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

protected:
    void initNodeBase();

    // 通用属性
    RealAttribute *m_pXPositionAttribute = nullptr;
    RealAttribute *m_pYPositionAttribute = nullptr;
    RealAttribute *m_pZPositionAttribute = nullptr;

    // 宽度和高度属性
    RealAttribute *m_pWidthAttribute = nullptr;
    RealAttribute *m_pHeightAttribute = nullptr;

    // 旋转属性
    RealAttribute *m_pRotateAttribute = nullptr;

    GraphicsItem *m_item = nullptr;

private slots:
    void onXYSuffixChanged(const QVariant &value);
private:
    QList<AttributeGroup*> m_groupList;
    int m_nodeType;
    QString m_name;     // 节点名字

};

#endif
