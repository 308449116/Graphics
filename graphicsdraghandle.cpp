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

    //移动处理
    m_view->moveItem(m_items, m_lastScenePos - m_pressedScenePos);
//    m_item->setPos(m_initialPos + m_lastScenePos - m_pressedScenePos);
//    m_selection->updateGeometry();
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
                m_selection->hide(false);
            }
        } else {
            setSelected(false);
            return QVariant::fromValue<bool>(false);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
