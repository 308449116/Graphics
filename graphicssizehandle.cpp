#include "graphicssizehandle.h"
#include "graphicsselection.h"
#include "graphicsitem.h"
#include "viewgraphics.h"
#include "common.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

GraphicsSizeHandle::GraphicsSizeHandle(int handleType, ViewGraphics *view, GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent), m_view(view)
{
    m_localRect = QRectF(-SIZE_HANDLE_WIDTH/2, -SIZE_HANDLE_WIDTH/2,
                         SIZE_HANDLE_WIDTH, SIZE_HANDLE_WIDTH);
    setZValue(2);
}

QPointF GraphicsSizeHandle::getOppositePos()
{
    return m_selection->opposite(m_handleType);
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

    m_scaleX = endOffset.x() / beginOffset.x();
    m_scaleY = endOffset.y() / beginOffset.y();

    switch (m_handleType) {
    case GraphicsHandle::Right:
    case GraphicsHandle::Left:
        m_scaleY = 1;
        break;
    case GraphicsHandle::Top:
    case GraphicsHandle::Bottom:
        m_scaleX = 1;
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
    m_item->stretch(m_scaleX, m_scaleY, m_item->mapFromScene(m_oppositePos));
//    m_item->updateCoordinate();
//    qreal width = m_item->width();
//    qreal height = m_item->height();
//    m_selection->updateGeometry(QRectF(-width / 2, -height / 2, width, height));

//    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsSizeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_item->updateCoordinate();
    m_selection->updateGeometry();
    m_selection->setOpacity(1);
    m_view->resizeItem(m_handleType, m_item, QPointF(m_scaleX, m_scaleY), true);
    QGraphicsItem::mouseReleaseEvent(event);
}
