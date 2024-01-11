#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QMap>
#include <QHash>
#include <QSharedPointer>

#include "common.h"
#include "graphicsabstracttemplate.h"

class ViewGraphics;
class GraphicsSelectionManager;

class GraphicsItemManager : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsItemManager(QObject *parent = nullptr);
    ~GraphicsItemManager();

    // 创建图元
    QSharedPointer<GraphicsAbstractItem> createGraphicsItem(
        GraphicsItemType type, const QString& itemName = "", QGraphicsItem *parent = nullptr);

    // 创建图元组
    QSharedPointer<GraphicsAbstractItem> createGraphicsItemGroup(
        QList<QSharedPointer<GraphicsAbstractItem> > items,
        const QString& itemName = "", QGraphicsItem *parent = nullptr);

    // 删除图元
    void deleteGraphicsItem(QSharedPointer<GraphicsAbstractItem> item);

    // 获取图元显示名
    QString getItemDisplayName(GraphicsItemType type);

    // 根据图元类型获取图元数
    int getItemCounts(GraphicsItemType type);

    // 取消分组
    void ungroup(QSharedPointer<GraphicsAbstractItem> item, GraphicsSelectionManager *selectionManager, ViewGraphics *view);

    void cleanAll();

private:
    void manageItem(QSharedPointer<GraphicsAbstractItem> item, const QString& itemName);

private:
    QHash<QString, QSharedPointer<GraphicsAbstractItem>> m_nameHash;
    QMap<GraphicsItemType, int> m_countMap;
};

#endif // GRAPHICSITEMMANAGER_H
