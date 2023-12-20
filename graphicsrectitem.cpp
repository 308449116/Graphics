#include "graphicsrectitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#define PI 3.1416

GraphicsRectItem::GraphicsRectItem(const QRectF &rect, GraphicsItem *parent)
    : GraphicsItem(parent)
{
    m_width = rect.width();
    m_height = rect.height();
    m_localRect = m_initialRect = rect;
    m_originPoint = QPointF(0,0);
    m_ratio = m_width / m_height;
}

void GraphicsRectItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
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

void GraphicsRectItem::updateCoordinate()
{
    QPointF pt1, pt2, delta;
    pt1 = mapToScene(transformOriginPoint());
    pt2 = mapToScene(m_localRect.center());
    delta = pt1 - pt2;
    qDebug() << "transformOriginPoint111:" << mapToScene(transformOriginPoint());
    qDebug() << "rotation11111:" << rotation();

    qDebug() << "transformOriginPoint:" << transformOriginPoint();
    qDebug() << "m_localRect.center:" << m_localRect.center();
    qDebug() << "delta:" << delta;
    if (!parentItem()) {
        prepareGeometryChange();
        m_localRect = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
        m_width = m_localRect.width();
        m_height = m_localRect.height();
        setTransform(transform().translate(delta.x(), delta.y()));
        setTransformOriginPoint(m_localRect.center());
        moveBy(-delta.x(), -delta.y());
        setTransform(transform().translate(-delta.x(), -delta.y()));
        m_oppositePos = QPointF(0,0);
    }
    qDebug() << "rotation2222:" << rotation();
    qDebug() << "transformOriginPoint222:" << mapToScene(transformOriginPoint());

    m_initialRect = m_localRect;
    m_ratio = m_width / m_height;
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
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(m_localRect);

    painter->setPen(Qt::blue);
    painter->drawLine(QLine(QPoint(m_oppositePos.x()-6,m_oppositePos.y()),QPoint(m_oppositePos.x()+6,m_oppositePos.y())));
    painter->drawLine(QLine(QPoint(m_oppositePos.x(),m_oppositePos.y()-6),QPoint(m_oppositePos.x(),m_oppositePos.y()+6)));
}

void GraphicsRectItem::rotate(QPointF rotatePos, QPointF lastPos)
{
//    //旋转处理
//    qDebug() << "处理旋转开始...";

//    QPointF origin = this->mapToScene(this->boundingRect().center());
//    this->setTransformOriginPoint(this->boundingRect().center());

//    qDebug() << "Operator origin:" << origin;
//    qDebug() << "Operator center:" << this->boundingRect().center();

//    qreal len_y = m_lastScenePos.y() - origin.y();
//    qreal len_x = m_lastScenePos.x() - origin.x();
//    qreal angle = atan2(len_y, len_x) * 180 / PI;
//    qDebug() << "len_x:" << len_x << "len_y:" << len_y;
//    qDebug() << "Operator rotation:" << this->rotation();
//    qDebug() << "Operator int(angle - lastAngle):" << int(angle - m_lastAngle);
//    qDebug() << "Operator angle1111:" << angle;

//    angle = m_currentAngle + int(angle - m_lastAngle) ;

//    if ( angle > 360 )
//        angle -= 360;
//    if ( angle < -360 )
//        angle+=360;

//    qDebug() << "Operator angle2222:" << angle;
//    this->setRotation( angle );
}
