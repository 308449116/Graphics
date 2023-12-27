#include "graphicsitemmanager.h"
#include "graphicsitem.h"
#include "graphicsrectitem.h"
#include "graphicstextitem.h"
#include "scenegraphics.h"

GraphicsItemManager::GraphicsItemManager(SceneGraphics *scene, QObject *parent)
    : QObject{parent}, m_scene{scene}
{
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_countMap.insert(static_cast<GraphicsItemType>(i), 0);
    }
}

QSharedPointer<GraphicsItem> GraphicsItemManager::createGraphicsItem(GraphicsItemType type, const QString& itemName)
{
    QSharedPointer<GraphicsItem> item;
    switch (type) {
    case GraphicsItemType::RectItem: {
        item = QSharedPointer<GraphicsItem>( new GraphicsRectItem(QRectF(-50, -50, 100, 100)) );
        break;
    }
    case GraphicsItemType::TextItem: {
        item = QSharedPointer<GraphicsItem>( new GraphicsTextItem("jkpg") );
        break;
    }
    case GraphicsItemType::BarcodeItem:
        break;
    default:
        break;
    }

    if (item.isNull()) return item;

    item->moveBy(item->width()/2, item->height()/2);
    m_scene->addItem(item.data());

    // 获取图元名
    QString tempName = itemName;
    if (tempName.isEmpty() || m_nameHash.find(tempName) != m_nameHash.end())
    {
        // 自动生成图元名
        do {
            tempName = QString("%1_%2").arg(getItemDisplayName(type)).arg(m_countMap[type]++);
        } while (m_nameHash.find(tempName) != m_nameHash.end());
    }
    item->setItemName(tempName);

    // 添加到哈希表中
    m_nameHash.insert(tempName, item);
    return item;
}

void GraphicsItemManager::deleteGraphicsItem(QSharedPointer<GraphicsItem> item)
{
    if (item.isNull()) return;

    m_scene->removeItem(item.data());
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
    default:
        return "";
    }

    return "";
}

int GraphicsItemManager::getItemCounts(GraphicsItemType type)
{
    return m_countMap[type];
}

void GraphicsItemManager::cleanAll()
{
    m_nameHash.clear();

    // 重新计数
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_countMap[static_cast<GraphicsItemType>(i)] = 0;
    }
}
