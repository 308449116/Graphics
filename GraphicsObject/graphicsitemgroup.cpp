#include "graphicsitemgroup.h"
#include "graphicsitem.h"
//#include "graphicsselection.h"
#include "common.h"

#include <QPainter>

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem{parent}
{
    m_itemGroup = new QGraphicsItemGroup(parentItem);
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsItemGroup::GraphicsItemGroup(QList<QSharedPointer<GraphicsItem> > items, QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem{parent}
{
    m_itemGroup = new QGraphicsItemGroup(parentItem);
    foreach (auto item, items){
    QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->subItem()->parentItem());
        if ( !g ) {
            m_itemGroup->addToGroup(item->subItem());
        }
    }

//    m_localRect = QGraphicsItemGroup::boundingRect();
//    m_width = m_localRect.width();
//    m_height = m_localRect.height();
//    setTransformOriginPoint(m_localRect.center());
//    m_oppositePos = m_localRect.center();
//    m_initialRect = m_localRect;
}

GraphicsItemGroup::~GraphicsItemGroup()
{
    m_childItems.clear();
}

int GraphicsItemGroup::type() const
{
    return GraphicsItemType::GroupItem;
}

//QRectF GraphicsItemGroup::boundingRect() const
//{
//    return getRect();
//}

//void GraphicsItemGroup::updateCoordinate(bool isGroup)
//{
//    foreach (QGraphicsItem *item , childItems()) {
//        GraphicsItem *abstractItem = qgraphicsitem_cast<GraphicsItem*>(item);
//        if (abstractItem) {
//            qDebug() << "isGroup:" << isGroup;

//            abstractItem->updateCoordinate(true);
//        }
//    }

////    qDebug() << "2222222222 transformOriginPoint:" << transformOriginPoint();
////    qDebug() << "2222222222 m_localRect.center():" << m_localRect.center();
////    qDebug() << "2222222222 delta:" << delta;
//    if (m_localRect.isNull()) {
//        m_localRect = QGraphicsItemGroup::boundingRect();
//        qDebug() << "m_localRect:" << m_localRect;
//    }

//    QPointF pt1, pt2, delta;
//    pt1 = mapToScene(transformOriginPoint());
//    pt2 = mapToScene(m_localRect.center());
//    delta = pt1 - pt2;
//    //    if (!parentItem()) {
//    prepareGeometryChange();
////    m_localRect = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
//    m_width = m_localRect.width();
//    m_height = m_localRect.height();
//    setTransform(transform().translate(delta.x(), delta.y()));
//    setTransformOriginPoint(m_localRect.center());
//    moveBy(-delta.x(), -delta.y());
////    setTransform(transform().translate(-delta.x(), -delta.y()));
//    m_oppositePos = m_localRect.center();
//    //    }

//    m_initialRect = m_localRect;
//    m_ratio = m_width / m_height;
//}

void GraphicsItemGroup::updateCoordinate()
{
    foreach (auto childItem , this->getChildItems()) {
        childItem->updateCoordinate();
    }

    if (m_localRect.isNull()) {
        m_localRect = m_itemGroup->boundingRect();
        qDebug() << "m_localRect:" << m_localRect;
    }

    QPointF pt1,pt2,delta;
    pt1 = m_itemGroup->mapToScene(m_itemGroup->transformOriginPoint());
    pt2 = m_itemGroup->mapToScene(m_localRect.center());
    delta = pt1 - pt2;

//    qDebug() << "2222222222 transformOriginPoint:" << transformOriginPoint();
//    qDebug() << "2222222222 m_localRect.center():" << m_localRect.center();
//    qDebug() << "2222222222 delta:" << delta;
    m_initialRect = m_localRect;
    m_width = m_localRect.width();
    m_height = m_localRect.height();
    //    m_localRect = QRectF(-m_width/2,-m_height/2,m_width,m_height);
    m_itemGroup->setTransform(m_itemGroup->transform().translate(delta.x(),delta.y()));
    m_itemGroup->setTransformOriginPoint(m_localRect.center());
    m_itemGroup->moveBy(-delta.x(),-delta.y());
    m_oppositePos = m_localRect.center();
    //   setTransform(transform().translate(-delta.x(),-delta.y()));
//    qDebug() << "3333333333 transformOriginPoint:" << transformOriginPoint();
//    qDebug() << "3333333333 delta:" << this->boundingRect();
}

void GraphicsItemGroup::setRotation(qreal newAngle)
{
    if (m_currentAngle == newAngle) return;

    m_lastAngle = m_currentAngle;
    m_currentAngle = newAngle;

    foreach (auto childItem, this->getChildItems()) {
        setChildItemRotation(childItem);
    }

    m_itemGroup->setRotation(newAngle);
}

void GraphicsItemGroup::setChildItemRotation(QSharedPointer<GraphicsItem> item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        foreach (auto childItem, item->getChildItems()) {
            setChildItemRotation(childItem);
        }
    }

    item->setGroupAngle(item->groupAngle() + (m_currentAngle - m_lastAngle));
}

QSharedPointer<GraphicsItem> GraphicsItemGroup::duplicate() const
{
    QList<QSharedPointer<GraphicsItem> > items = duplicateItems();
    qDebug() << "GraphicsItemGroup duplicateItems count:" << items.count();

    GraphicsItemGroup *itemGroup = new GraphicsItemGroup(items);
    itemGroup->updateCoordinate();
    itemGroup->subItem()->setPos(m_itemGroup->pos().x() + m_width, m_itemGroup->pos().y());
//    itemGroup->subItem()->setPen(pen());
//    itemGroup->subItem()->setBrush(brush());
    itemGroup->subItem()->setTransform(m_itemGroup->transform());
    itemGroup->subItem()->setTransformOriginPoint(m_itemGroup->transformOriginPoint());
    itemGroup->subItem()->setRotation(m_itemGroup->rotation());
    itemGroup->subItem()->setScale(m_itemGroup->scale());
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
    m_width = m_localRect.width();
    m_height = m_localRect.height();
}

void GraphicsItemGroup::addToGroup(QSharedPointer<GraphicsItem> item)
{
//    setItemZValue(item);
    m_itemGroup->addToGroup(item->subItem());
    m_childItems.insert(item);

//    GraphicsItem *childItem = dynamic_cast<GraphicsItem*>(item.data());
//    QObject::connect(childItem, &GraphicsItem::sendPararenItemGeometryChange, this, [this](){
//        GraphicsSelection *selection = this->selection();
//        if (selection) {
//            if (!selection->isActived()) {
//                GraphicsItem *item = dynamic_cast<GraphicsItem *>(sender());
//                qDebug() << "GraphicsItem::sendPararenItemGeometryChange 111111111" << QGraphicsItemGroup::boundingRect();
//                QTransform itemTransform = item->itemTransform(this);
//                m_localRect |= itemTransform.mapRect(item->boundingRect() | item->childrenBoundingRect());
//                updateCoordinate(true);
//                selection->updateHandle();
////                item->selection()->updateHandle();
////                emit sendUpdateHandle();
//            }
//        }
//    });

//    QTransform itemTransform = item->itemTransform(this);
//    m_localRect |= itemTransform.mapRect(item->boundingRect() | item->childrenBoundingRect());

//    m_localRect = QGraphicsItemGroup::boundingRect();
//    m_width = m_localRect.width();
//    m_height = m_localRect.height();
//    setTransformOriginPoint(m_localRect.center());
//    m_oppositePos = m_localRect.center();
//    m_initialRect = m_localRect;
}

//void GraphicsItemGroup::setItemZValue(QSharedPointer<GraphicsItem> item)
//{
//    if (item->type() == GraphicsItemType::GroupItem) {
//        foreach (auto childItem, item->getChildItems()) {
//            setItemZValue(childItem);
//        }
//    }

//    if (item->parentItem()) {
//        item->setZValue(item->zValue() + 1);
//    }
//}

void GraphicsItemGroup::removeFromGroup(QSharedPointer<GraphicsItem> item)
{
    GraphicsItem *childItem = dynamic_cast<GraphicsItem*>(item.data());
    QObject::disconnect(childItem, nullptr, this, nullptr);
    m_itemGroup->removeFromGroup(item->subItem());
    m_childItems.remove(item);
//    m_localRect = childrenBoundingRect();
}

//QVariant GraphicsItemGroup::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    qDebug() << "111111111111111111";

//    if ( change == QGraphicsItem::ItemRotationHasChanged ) {
//        qreal newAngle = value.toDouble();
//        qreal oldAngel = this->rotation();
//        qDebug() << "newAngle:" << newAngle << "  oldAngel:" << oldAngel;
//        foreach (auto childItem, this->getChildItems()) {
//            childItem->setCurrentGroupAngle(newAngle);
//            childItem->setGroupAngle(childItem->groupAngle() + (newAngle - oldAngel));
//        }
//    }

//    return QGraphicsItem::itemChange(change, value);
//}

//QVariant GraphicsItemGroup::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    if ( change == QGraphicsItem::ItemPositionChange ||
//        change == QGraphicsItem::ItemChildAddedChange ||
//        change == QGraphicsItem::ItemChildRemovedChange ||
//        change == QGraphicsItem::ItemRotationChange ||
//        change == QGraphicsItem::ItemScaleChange) {
//        if (!this->getItemParent().isNull()) {
//            emit this->sendPararenItemGeometryChange();
//        }
//    }

//    return QGraphicsItem::itemChange(change, value);
//}


QList<QSharedPointer<GraphicsItem> > GraphicsItemGroup::duplicateItems() const
{
    QList<QSharedPointer<GraphicsItem> > copylist;

    foreach (auto childItem, this->getChildItems()) {
        auto copyItem = childItem->duplicate();
        copyItem->subItem()->setPos(childItem->subItem()->pos());
        copylist.append(copyItem);
    }

    return copylist;
}

//void GraphicsItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(widget)
//    Q_UNUSED(option)

//    painter->setPen(m_pen);
//    painter->setBrush(m_brush);
////    painter->drawRect(m_localRect);

//    painter->setPen(Qt::blue);
//    painter->drawLine(QLine(QPoint(m_oppositePos.x()-6, m_oppositePos.y()),QPoint(m_oppositePos.x()+6, m_oppositePos.y())));
//    painter->drawLine(QLine(QPoint(m_oppositePos.x(), m_oppositePos.y()-6),QPoint(m_oppositePos.x(), m_oppositePos.y()+6)));
//}
