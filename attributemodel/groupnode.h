#ifndef GROUPNODE_H
#define GROUPNODE_H

#include "itemnodebase.h"

class IntAttribute;
class GroupNode : public ItemNodeBase
{
public:
    GroupNode(GraphicsItem *item);
    ~GroupNode();

    void saveToXml(QXmlStreamWriter *xml) override;

    void loadFromXml(QXmlStreamReader *xml) override;

private:
    void initAttribute();

    IntAttribute *m_nodeNumAttribute = nullptr;
};
#endif // GROUPNODE_H
