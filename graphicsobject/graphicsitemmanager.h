#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QMap>
#include <QHash>
#include <QSharedPointer>

#include "graphicsitem.h"
#include "viewgraphics.h"

class AttributeBase;
class GraphicsSelectionManager;

class GraphicsItemManager : public QObject
{
    Q_OBJECT

public:

    static GraphicsItemManager* getInstance();

    // 创建图元
    GraphicsItem *createGraphicsItem(
        GraphicsItemType type, const QString& itemName = "", QGraphicsItem *parent = nullptr);

    // 创建图元组
    GraphicsItem *createGraphicsItemGroup(
        QList<GraphicsItem *> items,
        const QString& itemName = "", QGraphicsItem *parent = nullptr);

    // 删除图元
//    void deleteGraphicsItem(GraphicsItem *item);

    // 获取图元显示名
    QString getItemDisplayName(GraphicsItemType type);

    // 根据图元类型获取图元数
    int getItemCounts(GraphicsItemType type);

    // 取消分组
//    void ungroup(GraphicsItem *item, GraphicsSelectionManager *selectionManager, ViewGraphics *view);

    void cleanAll();

    int itemCount();

    void addItem(GraphicsItem *item);

    void removeItem(const QString &uid);

    // 设置/获取当前的view
    void setCurrentGraphicsView(ViewGraphics *view);
    ViewGraphics *getCurrentGraphicsView();

    void loadGraphicsItem(QXmlStreamReader *xml);

    GraphicsItem *loadGraphicsItemGroup(QXmlStreamReader *xml);

    GraphicsItemType getTypeByName(const QString &name);

private:
    explicit GraphicsItemManager(QObject *parent = nullptr);
    GraphicsItemManager(const GraphicsItemManager &) = delete;
    GraphicsItemManager &operator=(const GraphicsItemManager&) = delete;
    ~GraphicsItemManager();
    int getChildItemCount(GraphicsItem *item);
    void manageItem(GraphicsItem *item, const QString& itemName);

private:
    QHash<QString, GraphicsItem *> m_graphicsManager;
    QMap<GraphicsItemType, int> m_counterItemType;
    ViewGraphics *m_grphicsView = nullptr;
};

#endif // GRAPHICSITEMMANAGER_H
