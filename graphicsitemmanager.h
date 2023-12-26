#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QObject>
#include <QHash>
#include <QMap>
#include "common.h"

class SceneGraphics;
class GraphicsItem;

class GraphicsItemManager : public QObject
{
    Q_OBJECT

public:
    explicit GraphicsItemManager(SceneGraphics *scene, QObject *parent = nullptr);

    // 创建图元
    GraphicsItem *createGraphicsItem(GraphicsItemType type, const QString& itemName = "");

    // 删除图元
    void deleteGraphicsItem(GraphicsItem *item);

    // 获取图元显示名
    QString getItemDisplayName(GraphicsItemType type);

    // 根据图元类型获取图元数
    int getItemCounts(GraphicsItemType type);

    void cleanAll();

private:
    SceneGraphics *m_scene;
    QHash<QString, GraphicsItem*> m_nameHash;
    QMap<GraphicsItemType, int> m_countMap;
};

#endif // GRAPHICSITEMMANAGER_H
