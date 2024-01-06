#include "graphicsitemgroup.h"
#include "common.h"

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parent)
    : GraphicsAbstractTemplate <QGraphicsItemGroup>{parent}
{

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

    foreach (QGraphicsItem *item , childItems()) {
        GraphicsAbstractItem *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
        if (abstractItem) {
            abstractItem->updateCoordinate();
        }
    }
}

QSharedPointer<GraphicsAbstractItem> GraphicsItemGroup::duplicate() const
{
    QList<QSharedPointer<GraphicsAbstractItem> > items = duplicateItems();
    qDebug() << "GraphicsItemGroup duplicateItems count:" << items.count();

    GraphicsItemGroup *itemGroup = new GraphicsItemGroup();
    foreach (auto item, items) {
        qDebug() << "GraphicsItemGroup type:" << item->type();
        itemGroup->addToGroup(item.data());
    }

    itemGroup->m_localRect = m_localRect;
    itemGroup->m_initialRect = m_initialRect;
    itemGroup->m_width = m_width;
    itemGroup->m_height = m_height;
    itemGroup->setPos(pos().x() + width(), pos().y());
    itemGroup->setPen(pen());
    itemGroup->setBrush(brush());
    itemGroup->setTransform(transform());
    itemGroup->setTransformOriginPoint(transformOriginPoint());
    itemGroup->setRotation(rotation());
    itemGroup->setScale(scale());
    itemGroup->setZValue(zValue()+0.1);
    itemGroup->setItemName(this->getItemName().append("_copy"));
    itemGroup->updateCoordinate();

    QSharedPointer<GraphicsAbstractItem> shareItem = QSharedPointer<GraphicsAbstractItem>(
        qgraphicsitem_cast<GraphicsAbstractItem *>(itemGroup));

    GraphicsItemGroup *g = dynamic_cast<GraphicsItemGroup *>(shareItem.data());
    if (itemGroup) {
        qDebug() << "111 childItems count:" << itemGroup->childItems().count();
    } else {
        qDebug() << "111 QGraphicsItemGroup is null";
    }

    return shareItem;
}

void GraphicsItemGroup::stretch(qreal sx, qreal sy, const QPointF &origin)
{

}

QList<QSharedPointer<GraphicsAbstractItem> > GraphicsItemGroup::duplicateItems() const
{
    QList<QSharedPointer<GraphicsAbstractItem> > copylist;

    foreach (auto *item , childItems() ) {
        auto *abstractItem = qgraphicsitem_cast<GraphicsAbstractItem*>(item);
        if ( abstractItem ){
            auto copyItem = abstractItem->duplicate();
            copylist.append(copyItem);
        }
    }

    return copylist;
}

