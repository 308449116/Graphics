#include "graphicsdraghandle.h"
#include "graphicsselection.h"
#include "graphicsitem.h"
#include "viewgraphics.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

GraphicsDragHandle::GraphicsDragHandle(int handleType, ViewGraphics *view,
                                       GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent), m_view(view)
{

}

void GraphicsDragHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

//    qDebug() << "GraphicsDragHandle boundingRect" << m_item->boundingRect();
//    qDebug() << "GraphicsDragHandle boundingRect" << boundingRect();
    if (getState() & GraphicsHandleState::HandleActive) {
        painter->save();
        painter->setPen(Qt::DashLine);
        QRectF rect = mapRectFromItem(m_item.data(), m_item->getRect());
        painter->drawRect(rect);
//        painter->drawLine(QPointF(rect.center().x(), rect.center().y() + rect.height() / 2),
//                          QPointF(rect.center().x(), rect.center().y() + rect.height() / 2 + 14));
        painter->restore();
    }
}

void GraphicsDragHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    m_lastScenePos = m_pressedScenePos = event->scenePos();
    m_initialPos = m_item->pos();
    m_items.clear();

    QList<QGraphicsItem *> items = m_view->scene()->selectedItems();
    foreach (auto item, items) {
        GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
        if (handle->handleType() == GraphicsHandle::Drag) {
            m_items.push_back(std::make_pair(handle->item()->pos(), handle->item()));
        }
    }

}

void GraphicsDragHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastScenePos = event->scenePos();
    m_selection->setOpacity(0);

    //移动处理
    m_view->moveItems(m_items, m_lastScenePos - m_pressedScenePos, false);
//    m_item->setPos(m_initialPos + m_lastScenePos - m_pressedScenePos);
//    m_selection->updateGeometry();
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsDragHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setOpacity(1);

    //Undo/Redo 移动处理
    if (m_items.count() > 0 && m_lastScenePos != m_pressedScenePos) {
        m_view->moveItems(m_items, m_lastScenePos - m_pressedScenePos, true);
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant GraphicsDragHandle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(parentItem());
        if (!group) {
            if (value.toBool()) {
                setState(GraphicsHandleState::HandleActive);
                m_selection->show();
            } else {
                setState(GraphicsHandleState::HandleOff);
                m_selection->hide(false);
            }
        } else {
            setSelected(false);
            return QVariant::fromValue<bool>(false);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
