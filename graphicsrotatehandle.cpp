#include "graphicsrotatehandle.h"
#include "graphicsselection.h"
#include "graphicsitem.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#define PI 3.1416

GraphicsRotateHandle::GraphicsRotateHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent),
    m_lastAngle(0),
    m_currentAngle(0)
{
    m_rotatePixmap = QPixmap(":/icons/rotate.png");
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
    QPointF origin = m_item->mapToScene(m_item->getRect().center());
    qreal len_y = m_lastScenePos.y() - origin.y();
    qreal len_x = m_lastScenePos.x() - origin.x();
    qreal angle = atan2(len_y, len_x) * 180 / PI;

    m_lastAngle = angle;
    m_currentAngle = m_item->rotation();
//    QGraphicsItem::mousePressEvent(event);
}

void GraphicsRotateHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = event->scenePos();
    //移动处理
    QPointF origin = m_item->mapToScene(m_item->getRect().center());
//  item->setTransformOriginPoint(item->getRect().center());

    qreal len_y = m_lastScenePos.y() - origin.y();
    qreal len_x = m_lastScenePos.x() - origin.x();
    qreal angle = atan2(len_y, len_x) * 180 / PI;
    angle = m_currentAngle + int(angle - m_lastAngle) ;
    if ( angle > 360 )
        angle -= 360;
    if ( angle < -360 )
        angle+=360;

    m_item->setRotation( angle );
    m_selection->updateGeometry();
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
