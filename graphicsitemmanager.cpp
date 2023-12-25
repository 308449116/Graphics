#include "graphicsitemmanager.h"
#include "graphicsitem.h"
#include "graphicsrectitem.h"
#include "graphicstextitem.h"
#include "scenegraphics.h"

GraphicsItemManager::GraphicsItemManager(SceneGraphics *scene, QObject *parent)
    : QObject{parent}, m_scene{scene}
{

}

GraphicsItem *GraphicsItemManager::createGraphicsItem(GraphicsItemType type)
{
    GraphicsItem *item = nullptr;
    switch (type) {
    case GraphicsItemType::RectItem: {
        item = new GraphicsRectItem(QRectF(-50, -50, 100, 100));
        break;
    }
    case GraphicsItemType::TextItem: {
        item = new GraphicsTextItem("jkpg");
        break;
    }
    case GraphicsItemType::BarcodeItem:
        break;
    default:
        break;
    }

    if (item == nullptr) return item;

    item->moveBy(item->width()/2, item->height()/2);
    m_scene->addItem(item);
    return item;
}

void GraphicsItemManager::deleteGraphicsItem(GraphicsItem *item)
{
    if (item == nullptr) return;

    m_scene->removeItem(item);
    delete item;
    item = nullptr;
}
