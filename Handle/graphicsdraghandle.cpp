#include "graphicsdraghandle.h"
#include "graphicsselection.h"
#include "viewgraphics.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

GraphicsDragHandle::GraphicsDragHandle(int handleType, ViewGraphics *view,
                                       GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent), m_view(view)
{
    setState(GraphicsHandleState::HandleActive);
    setSelected(false);
//    setFocus();
//    setActive(true);
//    setSelected(true);
}

void GraphicsDragHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

//    qDebug() << "GraphicsDragHandle boundingRect" << m_item->boundingRect();
//    qDebug() << "GraphicsDragHandle boundingRect" << boundingRect();
//    if (getState() & GraphicsHandleState::HandleActive) {
        painter->save();
        painter->setPen(Qt::DashLine);
        QRectF rect = mapRectFromItem(m_item->subItem(), m_item->getRect());
//        qDebug() << "GraphicsDragHandle customPaint rect:"
//                 << rect;

        painter->drawRect(rect);
//        painter->drawLine(QPointF(rect.center().x(), rect.center().y() + rect.height() / 2),
//                          QPointF(rect.center().x(), rect.center().y() + rect.height() / 2 + 14));
        painter->restore();
//    }
}

void GraphicsDragHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "111 GraphicsDragHandle mousePressEvent event->modifiers:" << event->modifiers();
//    qDebug() << "111 GraphicsDragHandle mousePressEvent multiSelect:" << ((event->modifiers() & Qt::ControlModifier) != 0);
    QGraphicsItem::mousePressEvent(event);
    qDebug() << "========= mousePressEvent zValue:" << m_selection->zValue();
    qDebug() << "========= mousePressEvent rotation:" << m_item->rotation();
    qDebug() << "========= mousePressEvent groupAngle:" << m_item->groupAngle();
    qDebug() << "========= mousePressEvent initAngle:" << m_item->initAngle();
    qDebug() << "========= mousePressEvent pos:" << m_item->subItem()->pos();
    qDebug() << "========= mousePressEvent scenePos:" << m_item->subItem()->scenePos();
    qDebug();

    if (m_item->itemParent().isNull()) {
        m_lastPos = m_pressedPos = event->scenePos();
    } else {
        m_lastPos = m_pressedPos = m_item->itemParent()->subItem()->mapFromScene(event->scenePos());
    }
    qDebug() << "m_pressedPos:" << m_lastPos;
//    m_initialPos = m_item->subItem()->pos();
    m_items.clear();

    QList<QGraphicsItem *> items = m_view->scene()->selectedItems();
    foreach (auto item, items) {
        GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
        if (handle->handleType() == GraphicsHandle::Drag) {
            m_items.push_back(qMakePair(handle->item()->subItem()->pos(), handle->item()));

        }
    }
}

void GraphicsDragHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_item->itemParent().isNull()) {
        m_lastPos = event->scenePos();
    } else {
        m_lastPos = m_item->itemParent()->subItem()->mapFromScene(event->scenePos());
    }

    m_selection->setOpacity(0);
//    qDebug() << "m_lastPos:" << m_lastPos;
//    qDebug() << "m_pressedPos:" << m_pressedPos;
//    qDebug() << "m_lastPos - m_pressedPos:" << m_lastPos - m_pressedPos;

    //移动处理
    m_view->moveItems(m_items, m_lastPos - m_pressedPos);
//    m_item->subItem()->setPos(m_initialPos + (m_lastPos - m_pressedPos));
//    m_selection->updateHandle();
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsDragHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setOpacity(1);

    //Undo/Redo 移动处理
    if (m_items.count() > 0 && m_lastPos != m_pressedPos) {
        m_view->moveItemsByCmd(m_items, m_lastPos - m_pressedPos, true);
        for (const auto &[pos, item] : m_items) {
            if (!item->itemParent().isNull()) {
                emit item->sendGraphicsItemChange();
            }
        }
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
