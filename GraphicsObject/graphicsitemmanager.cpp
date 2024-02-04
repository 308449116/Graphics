#include "graphicsitemmanager.h"
#include "graphicsrectitem.h"
#include "graphicstextitem.h"
#include "graphicsitemgroup.h"
//#include "graphicsselectionmanager.h"
//#include "viewgraphics.h"

GraphicsItemManager::GraphicsItemManager(QObject *parent)
    : QObject{parent}
{
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_countMap.insert(static_cast<GraphicsItemType>(i), 0);
    }
}

GraphicsItemManager::~GraphicsItemManager()
{
    m_nameHash.clear();
    m_countMap.clear();
}

GraphicsItem *GraphicsItemManager::createGraphicsItem(
    GraphicsItemType type, const QString& itemName, QGraphicsItem *parent)
{
    GraphicsItem *item = nullptr;

    switch (type) {
    case GraphicsItemType::RectItem: {
        item = new GraphicsRectItem(QRectF(0, 0, 100, 100), parent);
        break;
    }
    case GraphicsItemType::TextItem: {
        item = new GraphicsTextItem(parent);
        break;
    }
    case GraphicsItemType::BarcodeItem:
        break;
    default:
        break;
    }

    if (item == nullptr) return item;

//    item->subItem()->moveBy(item->width()/2, item->height()/2);

    manageItem(item, itemName);
    return item;
}

//GraphicsItem *GraphicsItemManager::createGraphicsItemGroup(
//    QList<GraphicsItem *> items, const QString &itemName, QGraphicsItem *parent)
//{
//    QSharedPointer<GraphicsAbstractItemGroup> itemGroup;
//    itemGroup = QSharedPointer<GraphicsAbstractItemGroup> (new GraphicsItemGroup(items, parent));
//    itemGroup->updateCoordinate();

//    GraphicsItem *itemSharedPointer = itemGroup.dynamicCast<GraphicsItem>();
//    manageItem(itemSharedPointer, itemName);

//    return itemSharedPointer;
//}

GraphicsItem *GraphicsItemManager::createGraphicsItemGroup(
    QList<GraphicsItem *> items, const QString &itemName, QGraphicsItem *parent)
{
    GraphicsItemGroup *itemGroup = new GraphicsItemGroup(items, parent);
    itemGroup->updateCoordinate();

    manageItem(itemGroup, itemName);

    return itemGroup;
}

void GraphicsItemManager::manageItem(GraphicsItem *item, const QString& itemName)
{
    // 获取图元名
    QString tempName = itemName;
    if (tempName.isEmpty() || m_nameHash.find(tempName) != m_nameHash.end())
    {
        // 自动生成图元名
        do {
            tempName = QString("%1_%2").arg(getItemDisplayName(static_cast<GraphicsItemType>(item->type())))
                           .arg(m_countMap[static_cast<GraphicsItemType>(item->type())]++);
        } while (m_nameHash.find(tempName) != m_nameHash.end());
    }
    item->setItemName(tempName);

    // 添加到哈希表中
    m_nameHash.insert(tempName, item);
    qDebug() << "keys:" << m_nameHash.keys();
    qDebug() << "values:" << m_nameHash.values();
}

int GraphicsItemManager::itemCount()
{
    return m_nameHash.count();
}

void GraphicsItemManager::addItem(const QString &name, GraphicsItem *item)
{
    m_nameHash.insert(name, item);
}

void GraphicsItemManager::removeItem(const QString &name)
{
    m_nameHash.remove(name);
}

//void GraphicsItemManager::deleteGraphicsItem(GraphicsItem *item)
//{
//    if (item == nullptr) return;

//    if (item->type() == GraphicsItemType::GroupItem) {
//        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
//        foreach (auto childItem, itemGroup->getChildItems()) {
//            deleteGraphicsItem(childItem);
//        }
//    }

//    m_nameHash.remove(item->itemName());
//}

QString GraphicsItemManager::getItemDisplayName(GraphicsItemType type)
{
    switch (type) {
    case GraphicsItemType::RectItem:
        return "RectItem";
    case GraphicsItemType::TextItem:
        return "TextItem";
    case GraphicsItemType::BarcodeItem:
        return "BarcodeItem";
    case GraphicsItemType::GroupItem:
        return "GroupItem";
    default:
        return "";
    }

    return "";
}

int GraphicsItemManager::getItemCounts(GraphicsItemType type)
{
    return m_countMap[type];
}

//void GraphicsItemManager::ungroup(GraphicsItem *item, GraphicsSelectionManager *selectionManager, ViewGraphics *view)
//{
//    if (item->type() != GraphicsItemType::GroupItem) return;

//    GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
//    foreach (auto childItem, itemGroup->getChildItems()) {
//        qDebug() << "itemGroup->getChildItems().rotation:" << childItem->rotation();
//        itemGroup->removeFromGroup(childItem);

//        view->setZValue(childItem, -1);
//        childItem->setItemParent(nullptr);
//        selectionManager->show(childItem);
//        selectionManager->updateHandle(childItem);
//    }
//    view->deleteItem(item);
//}

void GraphicsItemManager::cleanAll()
{
    m_nameHash.clear();

    // 重新计数
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_countMap[static_cast<GraphicsItemType>(i)] = 0;
    }
}
