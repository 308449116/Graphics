#include "graphicsrotatehandle.h"
#include "graphicsselection.h"
#include "viewgraphics.h"
#include "common.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QtMath>
#define PI 3.14159265358979

GraphicsRotateHandle::GraphicsRotateHandle(int handleType, ViewGraphics *view,
                                           GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent),
    m_lastAngle(0),
    m_initAngle(0),
    m_view(view)
{
    m_rotatePixmap = QPixmap(":/icons/rotate_press.png");
    m_localRect = QRectF(-ROTATE_HANDLE_WIDTH / 2, -ROTATE_HANDLE_WIDTH / 2,
                         ROTATE_HANDLE_WIDTH ,ROTATE_HANDLE_WIDTH);
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
    m_lastPos = m_pressedPos = event->scenePos();
    QPointF origin = m_item->subItem()->mapToScene(m_item->getRect().center());
    qreal len_y = m_lastPos.y() - origin.y();
    qreal len_x = m_lastPos.x() - origin.x();
    qreal angle = qAtan2(len_y, len_x) * 180 / PI;

    m_lastAngle = angle;
    m_initAngle = m_item->rotation();
//    QGraphicsItem::mousePressEvent(event);
}

void GraphicsRotateHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastPos = event->scenePos();
    m_selection->setOpacity(0);

    //移动处理
    QPointF origin = m_item->subItem()->mapToScene(m_item->getRect().center());
//  item->setTransformOriginPoint(item->getRect().center());

    qreal len_y = m_lastPos.y() - origin.y();
    qreal len_x = m_lastPos.x() - origin.x();
    qreal angle = qAtan2(len_y, len_x) * 180 / PI;
    angle = m_initAngle + int(angle - m_lastAngle);
    if ( angle > 360 )
        angle -= 360;
    if ( angle < -360 )
        angle += 360;

//    qDebug() << "1111111 angle:" << angle;
    m_item->setRotation( angle );
//    m_item->subItem()->update();
    if (angle == 0 || angle == 90 || angle == 180 || angle == 360) {
        int x = floor(m_item->subItem()->pos().x() / GRID_SIZE) * GRID_SIZE;
        int y = floor(m_item->subItem()->pos().y() / GRID_SIZE) * GRID_SIZE;
        m_item->subItem()->setPos(x, y);
    }
    m_view->updateHandle(m_item);
//    updateHandle(m_item);
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsRotateHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (m_lastPos != m_pressedPos) {
        m_selection->setOpacity(1);
        m_view->rotateItemByCmd(m_item, m_initAngle);

        if (m_item->subItem()->parentItem()) {
            emit m_item->sendGraphicsItemChange();
        }
    }
    //    QGraphicsItem::mouseReleaseEvent(event);
}

//void GraphicsRotateHandle::updateHandle(GraphicsItem *item)
//{
//    if (item->type() == GraphicsItemType::GroupItem) {
//        foreach (auto childItem, item->getChildItems()) {
//            updateHandle(childItem);
//        }
//    }

//    m_view->updateHandle(item);
//}
