#include "graphicsitemmanager.h"
#include "graphicsrectitem.h"
#include "graphicstextitem.h"
#include "graphicsitemgroup.h"
#include "attributemodel/nodebase.h"
#include "utils/attribute_constants.h"

#include <QXmlStreamReader>

GraphicsItemManager::GraphicsItemManager(QObject *parent)
    : QObject{parent}
{
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_counterItemType.insert(static_cast<GraphicsItemType>(i), 0);
    }
}

GraphicsItemManager::~GraphicsItemManager()
{
    m_graphicsManager.clear();
    m_counterItemType.clear();
}

GraphicsItemManager *GraphicsItemManager::getInstance()
{
    static GraphicsItemManager manager;
    return &manager;
}

void GraphicsItemManager::loadGraphicsItem(QXmlStreamReader *xml)
{
    Q_ASSERT(xml->isStartElement() && xml->name().toString() == QString::fromUtf8(Utils::Constants::CANVAS));
    while (xml->readNextStartElement()) {
        GraphicsItem *item = nullptr;
        if (xml->name().toString() ==  QString::fromUtf8(Utils::Constants::GROUP)) {
            item = loadGraphicsItemGroup(xml);
        } else {
            GraphicsItemType type = getTypeByName(xml->name().toString());
            QString itemName = xml->attributes().value(Utils::Constants::ITEMNAME).toString();
            item = createGraphicsItem(type, itemName);
        }

        if (!item->loadFromXml(xml)) {
            delete item;
            item = nullptr;
        }

        if (item) {
            m_grphicsView->addItem(item);
        }
    }
}

GraphicsItem *GraphicsItemManager::loadGraphicsItemGroup(QXmlStreamReader *xml)
{
    qreal angle = xml->attributes().value(Utils::Constants::ROTATE).toDouble();
    qreal posx = xml->attributes().value(Utils::Constants::POSX).toDouble();
    qreal posy = xml->attributes().value(Utils::Constants::POSY).toDouble();
    QString itemName = xml->attributes().value(Utils::Constants::ITEMNAME).toString();
    QString uid = xml->attributes().value(Utils::Constants::ID).toString();

    GraphicsItem *item = nullptr;
    QList<GraphicsItem *> itemList;
    while (xml->readNextStartElement()) {
        if (xml->name().toString() ==  QString::fromUtf8(Utils::Constants::GROUP)) {
            item = loadGraphicsItemGroup(xml);
        } else {
            GraphicsItemType type = getTypeByName(xml->name().toString());
            QString itemName = xml->attributes().value(Utils::Constants::ITEMNAME).toString();
            item = createGraphicsItem(type, itemName);
        }

        if (!item->loadFromXml(xml)) {
            delete item;
            item = nullptr;
        }

        if (item) {
            itemList.append(item);
        }
    }

    if (!itemList.isEmpty()) {
        item = createGraphicsItemGroup(itemList, itemName);
        if (item) {
            item->setUid(uid);
            item->moveBy(posx, posy);
            item->setRotation(angle);
        }
    }

    return item;
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

    item->init();

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

    if (itemGroup == nullptr) return itemGroup;
    itemGroup->init();

    manageItem(itemGroup, itemName);
    itemGroup->getCurrentNode()->
        getAttribute(QString::fromUtf8(Utils::Constants::NODENUM))->
        setValue(getChildItemCount(itemGroup));
    return itemGroup;
}

int GraphicsItemManager::getChildItemCount(GraphicsItem * item) {
    int counter = 0;
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        for (auto childItem : itemGroup->getChildItems()) {
            counter += getChildItemCount(childItem);
        }
    } else {
        counter++;
    }

    return counter;
}

void GraphicsItemManager::manageItem(GraphicsItem *item, const QString& itemName)
{
    // 获取图元名
    QString tempName = itemName;
    if (tempName.isEmpty())
    {
        // 自动生成图元名
        tempName = QString("%1_%2").arg(getItemDisplayName(static_cast<GraphicsItemType>(item->type())))
                       .arg(m_counterItemType[static_cast<GraphicsItemType>(item->type())]++);
    }
    item->setItemName(tempName);

    item->getCurrentNode()->
        getAttribute(QString::fromUtf8(Utils::Constants::ID))->
        setValue(item->uid());

    // 添加到哈希表中
    m_graphicsManager.insert(item->uid(), item);

    item->updateBaseAttribute();
//    connect(item, &GraphicsItem::sendItemNameChanged,
//            this, [this](const QString &newName, const QString &oldName) {
//        GraphicsItem *item = dynamic_cast<GraphicsItem *>(sender());
//        if (m_graphicsManager.contains(newName)) {
//            item->getCurrentNode()->
//                getAttribute(QString::fromUtf8(Utils::Constants::ITEMNAME))->
//                setValue(oldName);
//            return;
//        }

//        if (m_graphicsManager.contains(oldName)) {
//            m_graphicsManager.remove(oldName);
//        }
//        m_graphicsManager.insert(newName, item);
//        qDebug() << "m_graphicsManager.count:" << m_graphicsManager.count();
//        qDebug() << "m_graphicsManager.keys:" << m_graphicsManager.keys();
//        qDebug() << "m_graphicsManager.values:" << m_graphicsManager.values();
//    });

//    qDebug() << "keys:" << m_graphicsManager.keys();
//    qDebug() << "values:" << m_graphicsManager.values();
}

int GraphicsItemManager::itemCount()
{
    return m_graphicsManager.count();
}

void GraphicsItemManager::addItem(GraphicsItem *item)
{
    m_graphicsManager.insert(item->uid(), item);
}

void GraphicsItemManager::removeItem(const QString &uid)
{
    m_graphicsManager.remove(uid);
}

void GraphicsItemManager::setCurrentGraphicsView(ViewGraphics *view)
{
    m_grphicsView = view;
}

ViewGraphics *GraphicsItemManager::getCurrentGraphicsView()
{
    return m_grphicsView;
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

//    m_graphicsManager.remove(item->itemName());
//}

QString GraphicsItemManager::getItemDisplayName(GraphicsItemType type)
{
    switch (type) {
    case GraphicsItemType::RectItem:
        return QString::fromUtf8(Utils::Constants::RECT);
    case GraphicsItemType::TextItem:
        return  QString::fromUtf8(Utils::Constants::TEXT);
    case GraphicsItemType::BarcodeItem:
        return  QString::fromUtf8(Utils::Constants::BARCODE);
    case GraphicsItemType::GroupItem:
        return  QString::fromUtf8(Utils::Constants::GROUP);
    default:
        return "";
    }

    return "";
}

GraphicsItemType GraphicsItemManager::getTypeByName(const QString& name)
{
    if (name == QString::fromUtf8(Utils::Constants::RECT))
        return GraphicsItemType::RectItem;
    else if (name == QString::fromUtf8(Utils::Constants::TEXT))
        return GraphicsItemType::TextItem;
    else if (name == QString::fromUtf8(Utils::Constants::BARCODE))
        return GraphicsItemType::BarcodeItem;
    else if (name == QString::fromUtf8(Utils::Constants::GROUP))
        return GraphicsItemType::GroupItem;

    return GraphicsItemType::TypeCount;
}

int GraphicsItemManager::getItemCounts(GraphicsItemType type)
{
    return m_counterItemType[type];
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
    m_graphicsManager.clear();

    // 重新计数
    for(int i = GraphicsItemType::RectItem; i < GraphicsItemType::TypeCount; i++) {
        m_counterItemType[static_cast<GraphicsItemType>(i)] = 0;
    }
}
