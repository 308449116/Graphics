#include "graphicsrectitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "common.h"

GraphicsRectItem::GraphicsRectItem(const QRectF &rect, QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem(parent)
{
    m_subItem = m_rectItem = new QGraphicsRectItem(rect, parentItem);
    m_localRect = m_initialRect = rect;
    m_rectItem->setTransformOriginPoint(rect.center());
    //    m_originPoint = QPointF(0,0);
    //    m_ratio = m_width / m_height;
}

void GraphicsRectItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());

//    m_oppositePos = origin;

    //    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_rectItem->setRect(m_localRect);
}

void GraphicsRectItem::updateCoordinate()
{
    auto angle = qDegreesToRadians(m_rectItem->rotation());

    auto p1 = m_localRect.center();
    auto origin = m_rectItem->transformOriginPoint();
    QPointF p2 = QPointF(0, 0);

    p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
    p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));

    auto diff = p1 - p2;
    m_rectItem->moveBy(-diff.x(), -diff.y());
    m_rectItem->setTransformOriginPoint(m_localRect.center());

    m_initialRect = m_localRect;
}


GraphicsItem *GraphicsRectItem::duplicate() const
{
    GraphicsRectItem *item = new GraphicsRectItem(m_localRect);
    item->setRotation(rotation());
    item->setScale(m_scaleX, m_scaleY);
    item->setGroupAngle(groupAngle());
    item->setItemName(this->itemName().append("_copy"));
    item->subItem()->setPos(m_rectItem->pos().x() + width(), m_rectItem->pos().y());
    item->subItem()->setTransform(m_rectItem->transform());
    return item;
}

//void GraphicsRectItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(widget)
//    Q_UNUSED(option)

//    painter->setPen(m_pen);
//    painter->setBrush(m_brush);
//    painter->drawRect(m_localRect);

//    painter->setPen(Qt::blue);
//    painter->drawLine(QLine(QPoint(m_oppositePos.x()-6, m_oppositePos.y()),QPoint(m_oppositePos.x()+6, m_oppositePos.y())));
//    painter->drawLine(QLine(QPoint(m_oppositePos.x(), m_oppositePos.y()-6),QPoint(m_oppositePos.x(), m_oppositePos.y()+6)));
//}

int GraphicsRectItem::type() const
{
    return GraphicsItemType::RectItem;
}
