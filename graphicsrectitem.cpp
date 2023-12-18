#include "graphicsrectitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

GraphicsRectItem::GraphicsRectItem(const QRectF &rect, GraphicsItem *parent)
    : GraphicsItem(parent)
{
    m_width = rect.width();
    m_height = rect.height();
    m_localRect = m_initialRect = rect;
    m_originPoint = QPointF(0,0);
}

void GraphicsRectItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());

    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_width = m_localRect.width();
    m_height = m_localRect.height();
}

void GraphicsRectItem::updateCoordinate()
{
    QPointF pt1,pt2,delta;

    pt1 = mapToScene(transformOriginPoint());
    pt2 = mapToScene(m_localRect.center());
    delta = pt1 - pt2;

    if (!parentItem()) {
        prepareGeometryChange();
        m_localRect = QRectF(-m_width/2, -m_height/2, m_width, m_height);
        m_width = m_localRect.width();
        m_height = m_localRect.height();
        setTransform(transform().translate(delta.x(), delta.y()));
        setTransformOriginPoint(m_localRect.center());
        moveBy(-delta.x(), -delta.y());
        setTransform(transform().translate(-delta.x(), -delta.y()));
    }
    m_initialRect = m_localRect;
}

void GraphicsRectItem::move(const QPointF &point)
{
    moveBy(point.x(),point.y());
}

GraphicsItem *GraphicsRectItem::duplicate() const
{
    GraphicsRectItem *item = new GraphicsRectItem(m_localRect);
    item->m_width = width();
    item->m_height = height();
    item->setPos(pos().x(),pos().y());
    item->setTransform(transform());
    item->setTransformOriginPoint(transformOriginPoint());
    item->setRotation(rotation());
    item->setScale(scale());
    item->setZValue(zValue()+0.1);
    item->updateCoordinate();
    return item;
}

void GraphicsRectItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

//    if (isSelected()) {
//        qDebug() << "isSelected 11111111111111";
//    } else {
//        qDebug() << "isSelected 222222222222222";
//    }
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(m_localRect);
}

