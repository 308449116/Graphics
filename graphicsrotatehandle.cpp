#include "graphicsrotatehandle.h"
#include "graphicsselection.h"
#include "graphicsitem.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QtMath>
#define PI 3.1416

GraphicsRotateHandle::GraphicsRotateHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent),
    m_lastAngle(0),
    m_currentAngle(0)
{
    m_rotatePixmap = QPixmap(":/icons/rotate_press.png");
    m_localRect = QRectF(-5, -5, 10 ,10);
}

void GraphicsRotateHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
//    qDebug() << "GraphicsRotateHandle boundingRect";
//    qDebug() << "GraphicsRotateHandle boundingRect" << m_item->boundingRect();
    painter->save();

//    QRectF tempRect = m_item->boundingRect();
//    m_localRect = QRectF(tempRect.left() + tempRect.width()/2 - m_rotateIconWidth/2,
//                          tempRect.bottom()+m_lineLen,
//                          m_rotateIconWidth, m_rotateIconWidth);

//    QPointF bottomLeft = m_item->mapToScene(tempRect.bottomLeft());
//    QPointF bottomRight = m_item->mapToScene(tempRect.bottomRight());
    painter->drawPixmap(m_localRect, m_rotatePixmap, m_rotatePixmap.rect());

//    painter->setPen(Qt::DashLine);
//    painter->drawLine(mapToScene(this->boundingRect().top()),
//            QPointF(bottomRight.x() + bottomLeft.x() / 2, (bottomRight.y() + bottomLeft.y()) / 2));
    painter->restore();
}


void GraphicsRotateHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = m_pressedScenePos = event->scenePos();
//    QPointF origin = m_item->item()->sceneBoundingRect().center();
//    QPointF origin = m_item->item()->mapToScene(m_item->boundingRect().center());
    QPointF origin = m_item->item()->mapToScene(m_item->originPos());
    qreal len_y = m_lastScenePos.y() - origin.y();
    qreal len_x = m_lastScenePos.x() - origin.x();
    qreal angle = qAtan2(len_y, len_x) * 180 / PI;

    m_lastAngle = angle;
    m_currentAngle = m_item->rotation();
//    QGraphicsItem::mousePressEvent(event);
}

static inline double sdot(double a, double b, double c, double d) {
    return a * b + c * d;
}
void GraphicsRotateHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = event->scenePos();
    //移动处理
//    QPointF origin = m_item->item()->sceneBoundingRect().center();
//    m_item->item()->setTransformOriginPoint(origin);
    QPointF origin = m_item->item()->mapToScene(m_item->originPos());
//    m_item->item()->setTransformOriginPoint(m_item->boundingRect().center());

    qreal len_y = m_lastScenePos.y() - origin.y();
    qreal len_x = m_lastScenePos.x() - origin.x();
    qreal angle = qAtan2(len_y, len_x) * 180 / PI;
    angle = m_currentAngle + int(angle - m_lastAngle) ;
    if ( angle > 360 )
        angle -= 360;
    if ( angle < -360 )
        angle+=360;

    qDebug() << "m_item->scaleX()" << m_item->scaleX();
    qDebug() << "origin:" << m_item->item()->transformOriginPoint();
    qDebug() << "angle:" << angle;
    qDebug() << "rotation:" << m_item->rotation();
    m_item->setRotation( angle );

//    QTransform transform;
////    QTransform transform2 = m_item->item()->transform();

//    qDebug() << "m_translationPos========:" << m_item->originPos();
////    QPointF pivot = m_item->item()->mapFromScene(m_item->originPos());
////    transform.translate(pivot.x(), pivot.y());
//    QPointF pivot = m_item->originPos();
//    transform.translate(pivot.x() * m_item->scaleX(), pivot.y() * m_item->scaleY());

//    transform.rotate(m_item->rotation());
//    transform.scale(m_item->scaleX(), m_item->scaleY());
//    transform.translate(-pivot.x(), -pivot.y());

//    const double a = qDegreesToRadians(angle);
//    double sina = sin(a);
//    double cosa = cos(a);
//    QTransform translate(1, 0, 0, 1, m_item->originPos().x(), m_item->originPos().y());
//    QTransform scale(m_item->scaleX(), 0, 0,  m_item->scaleY(), 0, 0);
//    QTransform rotate(cosa, sina, -sina, cosa, 0, 0);
//    QTransform translate2(1, 0, 0, 1, -boundingRect().center().x(), -boundingRect().center().y());
//    QTransform transform = scale * translate * rotate * translate2;

    double px = m_item->width() / 2 - m_item->oppositePos().x();
//    double px = m_item->oppositePos().x() + m_item->width() / 2;
    double py = m_item->oppositePos().y();
//    double px = m_item->originPos().x() * m_item->scaleX();
//    double py = m_item->originPos().y() * m_item->scaleY();
//    QPointF diff = m_item->getRect().center() - m_item->boundingRect().center();
//    double px =  m_item->width() * 0.5;
//    double py = m_item->height() * 0.5;

    const double a = qDegreesToRadians(angle);
    double sina = sin(a);
    double cosa = cos(a);
    double oneMinusCosa = 1 - cosa;

    QTransform rotate(cosa, sina, -sina, cosa, sdot(sina, py, oneMinusCosa, px), sdot(-sina, px, oneMinusCosa, py));
    QTransform scale(m_item->scaleX(), 0, 0, m_item->scaleY(), 0, 0);

    m_item->item()->setTransform(scale * rotate);
//        m_item->item()->setTransform(transform);
    m_selection->updateGeometry();
//    qDebug() << "GraphicsRotateHandle boundingRect" << m_item->boundingRect();
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsRotateHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    m_lastAngle = 0;
//    QGraphicsItem::mouseReleaseEvent(event);
}

//QRectF GraphicsRotateHandle::boundingRect() const
//{
//    if (m_item) {
//        return m_item->boundingRect();
//    }

//    return QRectF();
//}
