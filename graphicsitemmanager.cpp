#include "graphicsitemmanager.h"
#include "graphicsitem.h"
#include "graphicsrectitem.h"
#include "graphicstextitem.h"
#include "scenegraphics.h"

GraphicsItemManager::GraphicsItemManager(SceneGraphics *scene, QObject *parent)
    : QObject{parent}, m_scene{scene}
{
    for(int i = RectItem; i < TypeCount; i++) {
        m_countMap.insert(static_cast<GraphicsItemType>(i), 0);
    }
}

GraphicsItem *GraphicsItemManager::createGraphicsItem(GraphicsItemType type, const QString& itemName)
{
    GraphicsItem *item = nullptr;
    switch (type) {
    case RectItem: {
        item = new GraphicsRectItem(QRectF(-50, -50, 100, 100));
        break;
    }
    case TextItem: {
        item = new GraphicsTextItem("jkpg");
        break;
    }
    case BarcodeItem:
        break;
    default:
        break;
    }

    if (item == nullptr) return item;
    item->moveBy(item->width()/2, item->height()/2);
    m_scene->addItem(item);

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

void GraphicsItemManager::deleteGraphicsItem(GraphicsItem *item)
{
    if (item == nullptr) return;

    m_scene->removeItem(item);
//    delete item;
//    item = nullptr;
}

QString GraphicsItemManager::getItemDisplayName(GraphicsItemType type)
{
    switch (type) {
    case RectItem:
        return "RectItem";
    case TextItem:
        return "TextItem";
    case BarcodeItem:
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
    for(int i = RectItem; i < TypeCount; i++) {
        m_countMap[static_cast<GraphicsItemType>(i)] = 0;
    }
}
