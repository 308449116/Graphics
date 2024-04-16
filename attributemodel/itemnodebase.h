#ifndef ITEMNODEBASE_H
#define ITEMNODEBASE_H

#include "nodebase.h"

class GraphicsItem;
class RealAttribute;
class StringAttribute;
class ItemNodeBase : public NodeBase
{
public:
    ItemNodeBase(GraphicsItem *item);
    ItemNodeBase(NodeType type, GraphicsItem *item);
    ~ItemNodeBase();

    void saveToXml(QXmlStreamWriter *xml) override;

    void loadFromXml(QXmlStreamReader *xml) override;

private slots:
    void onXYSuffixChanged(const QVariant &value);

protected:
    void initNodeBase();

    // 通用属性
    RealAttribute *m_XPositionAttribute = nullptr;
    RealAttribute *m_YPositionAttribute = nullptr;
//    RealAttribute *m_ZPositionAttribute = nullptr;

    // 宽度和高度属性
    RealAttribute *m_widthAttribute = nullptr;
    RealAttribute *m_heightAttribute = nullptr;

    // 旋转属性
    RealAttribute *m_rotateAttribute = nullptr;

    //名字
    StringAttribute *m_nameAttribute = nullptr;

    // id 唯一标识
    StringAttribute *m_IDAttribute = nullptr;

    GraphicsItem *m_item = nullptr;

};
#endif // ITEMNODEBASE_H
