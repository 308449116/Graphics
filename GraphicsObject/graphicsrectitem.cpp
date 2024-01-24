#include "graphicsrectitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "common.h"

GraphicsRectItem::GraphicsRectItem(const QRectF &rect, QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem(parent)
{
    m_subItem = m_rectItem = new QGraphicsRectItem(rect, parentItem);
    m_width = rect.width();
    m_height = rect.height();
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
    m_width = m_localRect.width();
    m_height = m_localRect.height();
    m_rectItem->setRect(m_localRect);
}

void GraphicsRectItem::updateCoordinate()
{
    //    QPointF pt1, pt2, delta;
    //    pt1 = m_rectItem->mapToScene(m_rectItem->transformOriginPoint());
    //    pt2 = m_rectItem->mapToScene(m_localRect.center());
    //    delta = pt1 - pt2;
    //    qDebug() << "transformOriginPoint111:" << m_rectItem->mapToScene(m_rectItem->transformOriginPoint());
    //    qDebug() << "rotation11111:" << rotation();

    //    qDebug() << "transformOriginPoint:" << m_rectItem->transformOriginPoint();
    //    qDebug() << "m_localRect.center:" << m_localRect.center();
    //    qDebug() << "delta:" << delta;
    if (!m_rectItem->parentItem()) {
        //        prepareGeometryChange();
        //        m_localRect = m_rectItem->boundingRect();
        //        m_localRect = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
        //        m_width = m_localRect.width();
        //        m_height = m_localRect.height();
        //        m_rectItem->setTransform(m_rectItem->transform().translate(delta.x(), delta.y()));
        //        m_rectItem->setTransformOriginPoint(m_localRect.center());
        //        m_rectItem->moveBy(-delta.x(), -delta.y());
        //        m_rectItem->setTransform(m_rectItem->transform().translate(-delta.x(), -delta.y()));
        //        m_oppositePos = QPointF(0,0);
        // 解决有旋转角度的矩形，拉伸之后，再次旋转，旋转中心该仍然为之前坐标，手动设置为中心，会产生漂移的问题

        //        auto rr = m_rectItem->boundingRect();
        auto angle = qDegreesToRadians(m_rectItem->rotation());

        auto p1 = m_localRect.center();
        auto origin = m_rectItem->transformOriginPoint();
        QPointF p2 = QPointF(0, 0);

        p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
        p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));

        auto diff = p1 - p2;
        m_rectItem->moveBy(-diff.x(), -diff.y());
        m_rectItem->setTransformOriginPoint(m_localRect.center());
        //        m_rectItem->update();
    }
    //    qDebug() << "rotation2222:" << rotation();
    //    qDebug() << "transformOriginPoint222:" << mapToScene(transformOriginPoint());

    m_initialRect = m_localRect;
}


QSharedPointer<GraphicsItem> GraphicsRectItem::duplicate() const
{
    GraphicsRectItem *item = new GraphicsRectItem(m_localRect);
    //    item->m_width = width();
    //    item->m_height = height();
    //    item->setPos(pos().x(),pos().y());
    //    item->setTransform(transform());
    //    item->setTransformOriginPoint(transformOriginPoint());
    //    item->setRotation(rotation());
    //    item->setScale(scale());
    //    item->setZValue(zValue()+0.1);
    //    item->updateCoordinate();
    return QSharedPointer<GraphicsItem>(item);
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
