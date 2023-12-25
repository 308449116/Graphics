#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QObject>

class SceneGraphics;
class GraphicsItem;

class GraphicsItemManager : public QObject
{
    Q_OBJECT
public:
    enum GraphicsItemType
    {
        RectItem,
        TextItem,
        BarcodeItem,
        EllipseItem,
        ImageItem,
        TypeCount
    };

    explicit GraphicsItemManager(SceneGraphics *scene, QObject *parent = nullptr);

    // 创建节点
    GraphicsItem *createGraphicsItem(GraphicsItemType type);

    // 删除节点
    void deleteGraphicsItem(GraphicsItem *item);

private:
    SceneGraphics *m_scene;
};

#endif // GRAPHICSITEMMANAGER_H
