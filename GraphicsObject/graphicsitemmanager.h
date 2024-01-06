#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QMap>
#include <QHash>
#include <QSharedPointer>

#include "common.h"
#include "graphicsabstracttemplate.h"

class SceneGraphics;

class GraphicsItemManager : public QObject
{
    Q_OBJECT

public:
    explicit GraphicsItemManager(SceneGraphics *scene, QObject *parent = nullptr);

    // 创建图元
    QSharedPointer<GraphicsAbstractItem> createGraphicsItem(GraphicsItemType type, const QString& itemName = "");

    // 删除图元
    void deleteGraphicsItem(QSharedPointer<GraphicsAbstractItem> item);

    // 获取图元显示名
    QString getItemDisplayName(GraphicsItemType type);

    // 根据图元类型获取图元数
    int getItemCounts(GraphicsItemType type);

    void cleanAll();

private:
    SceneGraphics *m_scene;
    QHash<QString, QSharedPointer<GraphicsAbstractItem>> m_nameHash;
    QMap<GraphicsItemType, int> m_countMap;
};

#endif // GRAPHICSITEMMANAGER_H
