#include "graphicssizehandle.h"
#include "graphicsselection.h"
#include "graphicsitem.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

GraphicsSizeHandle::GraphicsSizeHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent)
{
    m_localRect = QRectF(-GRAPHICS_HANDLE_SIZE/2,
                             -GRAPHICS_HANDLE_SIZE/2, GRAPHICS_HANDLE_SIZE, GRAPHICS_HANDLE_SIZE);
    setZValue(2);
}

void GraphicsSizeHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setPen(Qt::SolidLine);
    painter->setBrush(QBrush(m_borderColor));
    painter->drawRect(QRectF(m_localRect));
    painter->restore();
}


void GraphicsSizeHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = m_pressedScenePos = event->scenePos();
    m_oppositePos = m_selection->opposite(m_handleType);
//    qDebug() << "mousePressEvent m_handleType:" << m_handleType
//             << "  oppositePos:" << m_oppositePos;

    if( m_oppositePos.x() == 0 )
        m_oppositePos.setX(1);
    if (m_oppositePos.y() == 0 )
        m_oppositePos.setY(1);

//    QGraphicsItem::mousePressEvent(event);
}

void GraphicsSizeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = event->scenePos();
    m_selection->setOpacity(0);
    QPointF beginOffset = m_item->mapFromScene(m_pressedScenePos) - m_item->mapFromScene(m_oppositePos);
    QPointF endOffset = m_item->mapFromScene(m_lastScenePos) - m_item->mapFromScene(m_oppositePos);
//    qDebug() << "m_pressedScenePos" << m_pressedScenePos
//        << " m_lastScenePos" << m_lastScenePos;

    qreal sx = endOffset.x() / beginOffset.x();
    qreal sy = endOffset.y() / beginOffset.y();

    switch (m_handleType) {
    case GraphicsHandle::Right:
    case GraphicsHandle::Left:
        sy = 1;
        break;
    case GraphicsHandle::Top:
    case GraphicsHandle::Bottom:
        sx = 1;
        break;
//                case GraphicsHandle::LeftTop:
//                case GraphicsHandle::LeftBottom:
//                case GraphicsHandle::RightTop:
//                case GraphicsHandle::RightBottom:
//                    qDebug() << "item->getRatio:" << item->getRatio();
//                    sy = sx * item->getRatio();
//                    break;
    default:
        break;
    }
//    qDebug() << "mouseMoveEvent sx:" << sx
//             << "  sy:" << sy;
    m_item->stretch(sx , sy , m_item->mapFromScene(m_oppositePos));
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsSizeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_item->updateCoordinate();
    m_selection->updateGeometry();
    m_selection->setOpacity(1);
    QGraphicsItem::mouseReleaseEvent(event);
}
