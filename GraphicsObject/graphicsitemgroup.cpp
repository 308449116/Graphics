#include "graphicsitemgroup.h"
#include "common.h"

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parent)
    : GraphicsAbstractTemplate <QGraphicsItemGroup>{parent}
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
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

void GraphicsItemGroup::updateCoordinate()
{
    foreach (QGraphicsItem *item , childItems()) {
        GraphicsAbstractItem *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
        if (abstractItem) {
            abstractItem->updateCoordinate();
        }
    }

    if (m_localRect.isNull()) {
        m_localRect = QGraphicsItemGroup::boundingRect();
    }

    QPointF pt1,pt2,delta;
    pt1 = mapToScene(transformOriginPoint());
    pt2 = mapToScene(m_localRect.center());
    delta = pt1 - pt2;

    m_initialRect = m_localRect;
    m_width = m_localRect.width();
    m_height = m_localRect.height();
    //    m_localRect = QRectF(-m_width/2,-m_height/2,m_width,m_height);
    setTransform(transform().translate(delta.x(),delta.y()));
    setTransformOriginPoint(m_localRect.center());
    moveBy(-delta.x(),-delta.y());
    //   setTransform(transform().translate(-delta.x(),-delta.y()));

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

void GraphicsItemGroup::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    foreach (auto childItem, getChildItems()) {
        childItem->stretch(sx, sy, childItem->mapFromItem(this, origin));
    }

    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());

    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_width = m_localRect.width();
    m_height = m_localRect.height();
}

void GraphicsItemGroup::addToGroup(QSharedPointer<GraphicsAbstractItem> item)
{
    this->addToGroup(item.data());
    m_childItems.insert(item);
}

void GraphicsItemGroup::removeFromGroup(QSharedPointer<GraphicsAbstractItem> item)
{
    this->removeFromGroup(item.data());
    m_childItems.remove(item);
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

    foreach (auto *item , childItems() ) {
        auto *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
        if ( abstractItem ) {
            auto copyItem = abstractItem->duplicate();
            copyItem->setPos(abstractItem->pos());
            copylist.append(copyItem);
        }
    }

    return copylist;
}
