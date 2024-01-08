#include "graphicsitemmanager.h"
#include "graphicsrectitem.h"
#include "graphicstextitem.h"
#include "graphicsitemgroup.h"
#include "graphicsselectionmanager.h"
#include "scenegraphics.h"

GraphicsItemManager::GraphicsItemManager(SceneGraphics *scene, QObject *parent)
    : QObject{parent}, m_scene{scene}
{
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_countMap.insert(static_cast<GraphicsItemType>(i), 0);
    }
}

QSharedPointer<GraphicsAbstractItem> GraphicsItemManager::createGraphicsItem(
    GraphicsItemType type, const QString& itemName, QGraphicsItem *parent)
{
    QSharedPointer<GraphicsAbstractItem> item;

    switch (type) {
    case GraphicsItemType::RectItem: {
        item = QSharedPointer<GraphicsAbstractItem>( new GraphicsRectItem(QRectF(-50, -50, 100, 100), parent) );
        break;
    }
    case GraphicsItemType::TextItem: {
        item = QSharedPointer<GraphicsAbstractItem>( new GraphicsTextItem("jkpg", parent) );
        break;
    }
    case GraphicsItemType::BarcodeItem:
        break;
    default:
        break;
    }

    if (item.isNull()) return item;

    item->moveBy(item->width()/2, item->height()/2);

    manageItem(item, itemName);
    return item;
}

//QSharedPointer<GraphicsAbstractItem> GraphicsItemManager::createGraphicsItemGroup(
//    QList<QSharedPointer<GraphicsAbstractItem> > items, const QString &itemName, QGraphicsItem *parent)
//{
//    QSharedPointer<GraphicsAbstractItemGroup> itemGroup;
//    itemGroup = QSharedPointer<GraphicsAbstractItemGroup> (new GraphicsItemGroup(items, parent));
//    itemGroup->updateCoordinate();

//    QSharedPointer<GraphicsAbstractItem> itemSharedPointer = itemGroup.dynamicCast<GraphicsAbstractItem>();
//    manageItem(itemSharedPointer, itemName);

//    return itemSharedPointer;
//}

QSharedPointer<GraphicsAbstractItem> GraphicsItemManager::createGraphicsItemGroup(
    QList<QSharedPointer<GraphicsAbstractItem> > items, const QString &itemName, QGraphicsItem *parent)
{
    GraphicsItemGroup *itemGroup = new GraphicsItemGroup(items, parent);
    itemGroup->updateCoordinate();

    QSharedPointer<GraphicsAbstractItem> itemSharedPointer = QSharedPointer<GraphicsAbstractItem>(
        qgraphicsitem_cast<GraphicsAbstractItem *>(itemGroup));
    manageItem(itemSharedPointer, itemName);

    return itemSharedPointer;
}

void GraphicsItemManager::manageItem(QSharedPointer<GraphicsAbstractItem> item, const QString& itemName)
{
    // 将图元添加到场景
    m_scene->addItem(item.data());

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
}

void GraphicsItemManager::deleteGraphicsItem(QSharedPointer<GraphicsAbstractItem> item)
{
    if (item.isNull()) return;

    m_scene->removeItem(item.data());

    if (item->type() == GraphicsItemType::GroupItem) {
        foreach (auto childItem, item->getChildItems()) {
            m_nameHash.remove(childItem->getItemName());
        }
    }

    m_nameHash.remove(item->getItemName());
//    delete item;
//    item = nullptr;
}

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

void GraphicsItemManager::ungroup(QSharedPointer<GraphicsAbstractItem> item, GraphicsSelectionManager *selectManager)
{
    if (item->type() != GraphicsItemType::GroupItem) return;

    qDebug() << "itemGroup->getChildItems().count:" << item->getChildItems().count();
    foreach (auto childItem, item->getChildItems()) {
        item->removeFromGroup(childItem);
        selectManager->show(childItem);
        selectManager->updateGeometry(childItem);
    }

    selectManager->removeItem(item);
}

//void GraphicsItemManager::ungroup(QSharedPointer<GraphicsAbstractItem> item, GraphicsSelectionManager *selectManager)
//{
//    GraphicsAbstractItem *ab = item.data();
//    GraphicsAbstractItemGroup *itemGroup  = dynamic_cast<GraphicsAbstractItemGroup *>(ab);
//    if (itemGroup) {
//        qDebug() << "itemGroup->getChildItems().count:" << itemGroup->getChildItems().count();
//        foreach (auto childItem, itemGroup->getChildItems()) {
//            //            itemGroup->removeFromGroup(childItem);
//            selectManager->show(childItem);
//        }
//    } else {
//        qDebug() << "itemGroup ============= ";
//    }

//    selectManager->removeItem(item);
//}

void GraphicsItemManager::cleanAll()
{
    m_nameHash.clear();

    // 重新计数
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_countMap[static_cast<GraphicsItemType>(i)] = 0;
    }
}
