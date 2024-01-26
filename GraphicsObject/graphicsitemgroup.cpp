#include "graphicsitemgroup.h"
#include "graphicsitem.h"
//#include "graphicsselection.h"
#include "common.h"

#include <QPainter>

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem{parent}
{
    m_subItem = m_itemGroup = new QGraphicsItemGroup(parentItem);
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsItemGroup::GraphicsItemGroup(QList<QGraphicsItem *> items, QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem{parent}
{
    m_subItem = m_itemGroup = new QGraphicsItemGroup(parentItem);
    foreach (auto item, items){
        m_itemGroup->addToGroup(item);
    }

    m_localRect = m_itemGroup->boundingRect();
    m_itemGroup->setTransformOriginPoint(m_localRect.center());
    m_oppositePos = m_localRect.center();
    m_initialRect = m_localRect;
}

//GraphicsItemGroup::GraphicsItemGroup(QList<QSharedPointer<GraphicsItem> > items, QGraphicsItem *parentItem, QObject *parent)
//    : GraphicsItem{parent}
//{
//    m_subItem = m_itemGroup = new QGraphicsItemGroup(parentItem);
//    foreach (auto item, items){
//        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->subItem()->parentItem());
//        if ( !g ) {
//            GraphicsItemGroup::addToGroup(item);
//        }
//    }

//    m_localRect = m_itemGroup->boundingRect();
//    m_itemGroup->setTransformOriginPoint(m_localRect.center());
//    m_oppositePos = m_localRect.center();
//    m_initialRect = m_localRect;
//}

GraphicsItemGroup::~GraphicsItemGroup()
{
    m_childItems.clear();
}

int GraphicsItemGroup::type() const
{
    return GraphicsItemType::GroupItem;
}

void GraphicsItemGroup::updateCoordinate()
{
    foreach (auto childItem , this->getChildItems()) {
        childItem->updateCoordinate();
    }

//    if (m_localRect.isNull()) {
//        m_localRect = m_itemGroup->boundingRect();
//        qDebug() << "m_localRect:" << m_localRect;
//    }

    auto angle = qDegreesToRadians(m_itemGroup->rotation());

    auto p1 = m_localRect.center();
    auto origin = m_itemGroup->transformOriginPoint();
    QPointF p2 = QPointF(0, 0);

    p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
    p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));

    auto diff = p1 - p2;
    m_itemGroup->moveBy(-diff.x(), -diff.y());
    m_itemGroup->setTransformOriginPoint(m_localRect.center());

    m_initialRect = m_localRect;

//    QPointF pt1,pt2,delta;
//    pt1 = m_itemGroup->mapToScene(m_itemGroup->transformOriginPoint());
//    pt2 = m_itemGroup->mapToScene(m_localRect.center());
//    delta = pt1 - pt2;

//    m_initialRect = m_localRect;
//    m_itemGroup->setTransform(m_itemGroup->transform().translate(delta.x(),delta.y()));
//    m_itemGroup->setTransformOriginPoint(m_localRect.center());
//    m_itemGroup->moveBy(-delta.x(),-delta.y());
//    m_oppositePos = m_localRect.center();
}

QSharedPointer<GraphicsItem> GraphicsItemGroup::duplicate() const
{
    QList<QSharedPointer<GraphicsItem> > items = duplicateItems();
    qDebug() << "GraphicsItemGroup duplicateItems count:" << items.count();

    GraphicsItemGroup *itemGroup = new GraphicsItemGroup(items);
    itemGroup->setRotation(rotation());
    itemGroup->setScale(m_scaleX, m_scaleY);
    itemGroup->subItem()->setPos(m_itemGroup->pos().x() + width(), m_itemGroup->pos().y());
//    itemGroup->subItem()->setPen(pen());
//    itemGroup->subItem()->setBrush(brush());
    itemGroup->subItem()->setTransform(m_itemGroup->transform());
    itemGroup->subItem()->setTransformOriginPoint(m_itemGroup->transformOriginPoint());
    itemGroup->subItem()->setZValue(m_itemGroup->zValue()+0.1);
    itemGroup->setItemName(this->itemName().append("_copy"));
    return QSharedPointer<GraphicsItem>(itemGroup);
}

QSet<QSharedPointer<GraphicsItem> > GraphicsItemGroup::getChildItems() const
{
    return m_childItems;
}

void GraphicsItemGroup::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    foreach (auto childItem, getChildItems()) {
        childItem->stretch(sx, sy, childItem->subItem()->mapFromItem(m_itemGroup, origin));
    }

    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());

    m_oppositePos = origin;

    m_localRect = trans.mapRect(m_initialRect);
}

void GraphicsItemGroup::addToGroup(GraphicsItem *item, QList<QGraphicsItem *> handle)
{
    m_itemGroup->addToGroup(item);
}

//void GraphicsItemGroup::addToGroup(QSharedPointer<GraphicsItem> item)
//{
//    m_itemGroup->addToGroup(item->subItem());
//    m_childItems.insert(item);
//    QObject::connect(item.data(), &GraphicsItem::sendGraphicsItemChange, this, [this](){
//        GraphicsItem *senderItem = dynamic_cast<GraphicsItem *>(sender());
//        QTransform itemTransform = senderItem->subItem()->itemTransform(m_itemGroup);
//        m_localRect |= itemTransform.mapRect(senderItem->subItem()->boundingRect() | senderItem->subItem()->childrenBoundingRect());
//        updateCoordinate();
//        emit sendUpdateHandle();
//    });

//    //    QTransform itemTransform = item->itemTransform(this);
//    //    m_localRect |= itemTransform.mapRect(item->boundingRect() | item->childrenBoundingRect());

//    //    m_localRect = QGraphicsItemGroup::boundingRect();
//    //    m_width = m_localRect.width();
//    //    m_height = m_localRect.height();
//    //    setTransformOriginPoint(m_localRect.center());
//    //    m_oppositePos = m_localRect.center();
//    //    m_initialRect = m_localRect;
//}

void GraphicsItemGroup::removeFromGroup(QGraphicsItem *item)
{
    m_itemGroup->removeFromGroup(item);
}

//void GraphicsItemGroup::removeFromGroup(QSharedPointer<GraphicsItem> item)
//{
//    QObject::disconnect(item.data(), nullptr, this, nullptr);
//    m_itemGroup->removeFromGroup(item->subItem());
//    m_childItems.remove(item);
//    //    m_localRect = childrenBoundingRect();
//}

QList<QGraphicsItem> GraphicsItemGroup::duplicateItems() const
{
    QList<QGraphicsItem> copylist;
    foreach (auto childItem, m_itemGroup->childItems()) {
        if (childItem->type() > QGraphicsItem::UserType) {
            GraphicsItem *customItem = dynami
        }
        auto copyItem = childItem->duplicate();
        copyItem->subItem()->setPos(childItem->subItem()->pos());
        copylist.append(copyItem);
    }

    return copylist;
}
