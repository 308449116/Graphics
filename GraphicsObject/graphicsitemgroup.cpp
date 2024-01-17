#include "graphicsitemgroup.h"
#include "graphicsitem.h"
#include "graphicsselection.h"
#include "common.h"

#include <QPainter>

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parent)
    : GraphicsAbstractTemplate <QGraphicsItemGroup>{parent}
{
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsItemGroup::GraphicsItemGroup(QList<QSharedPointer<GraphicsAbstractItem> > items, QGraphicsItem *parent)
    : GraphicsAbstractTemplate <QGraphicsItemGroup>{parent}
{
    foreach (auto item, items){
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if ( !g ) {
            GraphicsItemGroup::addToGroup(item);
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

QRectF GraphicsItemGroup::boundingRect() const
{
    return getRect();
}

//void GraphicsItemGroup::updateCoordinate(bool isGroup)
//{
//    foreach (QGraphicsItem *item , childItems()) {
//        GraphicsAbstractItem *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
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

void GraphicsItemGroup::updateCoordinate(bool isGroup)
{
    if (!isGroup) {
        foreach (QGraphicsItem *item , childItems()) {
            GraphicsAbstractItem *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
            if (abstractItem) {
                abstractItem->updateCoordinate(true);
            }
        }
    }

    if (m_localRect.isNull()) {
        m_localRect = QGraphicsItemGroup::boundingRect();
        qDebug() << "m_localRect:" << m_localRect;
    }

    QPointF pt1,pt2,delta;
    pt1 = mapToScene(transformOriginPoint());
    pt2 = mapToScene(m_localRect.center());
    delta = pt1 - pt2;

//    qDebug() << "2222222222 transformOriginPoint:" << transformOriginPoint();
//    qDebug() << "2222222222 m_localRect.center():" << m_localRect.center();
//    qDebug() << "2222222222 delta:" << delta;
    m_initialRect = m_localRect;
    m_width = m_localRect.width();
    m_height = m_localRect.height();
    //    m_localRect = QRectF(-m_width/2,-m_height/2,m_width,m_height);
    setTransform(transform().translate(delta.x(),delta.y()));
    setTransformOriginPoint(m_localRect.center());
    moveBy(-delta.x(),-delta.y());
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

    QGraphicsItemGroup::setRotation(newAngle);
}

void GraphicsItemGroup::setChildItemRotation(QSharedPointer<GraphicsAbstractItem> item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        foreach (auto childItem, item->getChildItems()) {
            setChildItemRotation(childItem);
        }
    }

    item->setGroupAngle(item->groupAngle() + (m_currentAngle - m_lastAngle));
}

QSharedPointer<GraphicsAbstractItem> GraphicsItemGroup::duplicate() const
{
    QList<QSharedPointer<GraphicsAbstractItem> > items = duplicateItems();
    qDebug() << "GraphicsItemGroup duplicateItems count:" << items.count();

    GraphicsItemGroup *itemGroup = new GraphicsItemGroup(items);
    itemGroup->updateCoordinate();
    itemGroup->setPos(pos().x() + m_width, pos().y());
    itemGroup->setPen(pen());
    itemGroup->setBrush(brush());
    itemGroup->setTransform(transform());
    itemGroup->setTransformOriginPoint(transformOriginPoint());
    itemGroup->setRotation(rotation());
    itemGroup->setScale(scale());
    itemGroup->setZValue(zValue()+0.1);
    itemGroup->setItemName(this->getItemName().append("_copy"));

    return QSharedPointer<GraphicsAbstractItem>(
        qgraphicsitem_cast<GraphicsAbstractItem *>(itemGroup));
}

QSet<QSharedPointer<GraphicsAbstractItem> > GraphicsItemGroup::getChildItems() const
{
    return m_childItems;
}

void GraphicsItemGroup::stretch(qreal sx, qreal sy)
{
    foreach (auto childItem, getChildItems()) {
        childItem->stretch(sx, sy);
    }

    const QPointF &origin = this->oppositePos();
    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());

    m_oppositePos = origin;

    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_width = m_localRect.width();
    m_height = m_localRect.height();
}

void GraphicsItemGroup::addToGroup(QSharedPointer<GraphicsAbstractItem> item)
{
//    setItemZValue(item);
    this->addToGroup(item.data());
    m_childItems.insert(item);

    GraphicsItem *childItem = dynamic_cast<GraphicsItem*>(item.data());
    QObject::connect(childItem, &GraphicsItem::sendPararenItemGeometryChange, this, [this](){
        GraphicsSelection *selection = this->selection();
        if (selection) {
            if (!selection->isActived()) {
                GraphicsItem *item = dynamic_cast<GraphicsItem *>(sender());
                qDebug() << "GraphicsItem::sendPararenItemGeometryChange 111111111" << QGraphicsItemGroup::boundingRect();
                QTransform itemTransform = item->itemTransform(this);
                m_localRect |= itemTransform.mapRect(item->boundingRect() | item->childrenBoundingRect());
                updateCoordinate(true);
                selection->updateHandle();
//                item->selection()->updateHandle();
//                emit sendUpdateHandle();
            }
        }
    });

//    QTransform itemTransform = item->itemTransform(this);
//    m_localRect |= itemTransform.mapRect(item->boundingRect() | item->childrenBoundingRect());

//    m_localRect = QGraphicsItemGroup::boundingRect();
//    m_width = m_localRect.width();
//    m_height = m_localRect.height();
//    setTransformOriginPoint(m_localRect.center());
//    m_oppositePos = m_localRect.center();
//    m_initialRect = m_localRect;
}

//void GraphicsItemGroup::setItemZValue(QSharedPointer<GraphicsAbstractItem> item)
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

void GraphicsItemGroup::removeFromGroup(QSharedPointer<GraphicsAbstractItem> item)
{
    GraphicsItem *childItem = dynamic_cast<GraphicsItem*>(item.data());
    QObject::disconnect(childItem, nullptr, this, nullptr);
    this->removeFromGroup(item.data());
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

void GraphicsItemGroup::addToGroup(QGraphicsItem *item)
{
    QGraphicsItemGroup::addToGroup(item);
}

void GraphicsItemGroup::removeFromGroup(QGraphicsItem *item)
{
    QGraphicsItemGroup::removeFromGroup(item);
}

QList<QSharedPointer<GraphicsAbstractItem> > GraphicsItemGroup::duplicateItems() const
{
    QList<QSharedPointer<GraphicsAbstractItem> > copylist;

    foreach (auto *item , childItems()) {
        auto *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
        if ( abstractItem ) {
            auto copyItem = abstractItem->duplicate();
            copyItem->setPos(abstractItem->pos());
            copylist.append(copyItem);
        }
    }

    return copylist;
}

void GraphicsItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setPen(m_pen);
    painter->setBrush(m_brush);
//    painter->drawRect(m_localRect);

    painter->setPen(Qt::blue);
    painter->drawLine(QLine(QPoint(m_oppositePos.x()-6, m_oppositePos.y()),QPoint(m_oppositePos.x()+6, m_oppositePos.y())));
    painter->drawLine(QLine(QPoint(m_oppositePos.x(), m_oppositePos.y()-6),QPoint(m_oppositePos.x(), m_oppositePos.y()+6)));
}
