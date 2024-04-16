#ifndef CANVASNODE_H
#define CANVASNODE_H

#include "nodebase.h"

class SceneGraphics;
class RealAttribute;
class CanvasNode : public NodeBase
{
public:
    CanvasNode(SceneGraphics *scene);
    ~CanvasNode();

    void saveToXml(QXmlStreamWriter *xml) override;

    void loadFromXml(QXmlStreamReader *xml) override;

private:
    void initAttribute();

    RealAttribute *m_widthAttribute = nullptr;
    RealAttribute *m_heightAttribute = nullptr;
    SceneGraphics *m_scene = nullptr;
};
#endif // CANVASNODE_H
