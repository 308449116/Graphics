#include "graphicsdraghandle.h"
#include "graphicsselection.h"
#include "graphicsitem.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

GraphicsDragHandle::GraphicsDragHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent)
{
}

void GraphicsDragHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
//    qDebug() << "GraphicsDragHandle boundingRect" << m_item->boundingRect();
//    painter->save();
//    painter->setPen(Qt::DashLine);
//    painter->setBrush(QBrush(Qt::red));
//    painter->drawRect(boundingRect());
//    painter->restore();
}

void GraphicsDragHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = m_pressedScenePos = event->scenePos();
    m_initialPos = m_item->pos();
    QGraphicsItem::mousePressEvent(event);
}

void GraphicsDragHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = event->scenePos();
    //移动处理
    m_item->setPos(m_initialPos + m_lastScenePos - m_pressedScenePos);
    m_selection->updateGeometry();
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsDragHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant GraphicsDragHandle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(parentItem());
        if (!group) {
            if (value.toBool()) {
                m_selection->show();
            } else {
                m_selection->hide();
            }
        } else {
            setSelected(false);
            return QVariant::fromValue<bool>(false);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
