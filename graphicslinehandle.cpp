#include "graphicslinehandle.h"
#include "graphicsitem.h"

#include <QGraphicsItem>
#include <QPainter>

GraphicsLineHandle::GraphicsLineHandle(
    int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    : GraphicsHandle(handleType, selection, parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable, false);
}

void GraphicsLineHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setPen(Qt::DashLine);
    QRectF rect = mapRectFromItem(m_item.data(), m_item->getRect());
    painter->drawLine(QPointF(rect.center().x(), rect.center().y() + rect.height() / 2),
                      QPointF(rect.center().x(), rect.center().y() + rect.height() / 2 + 14));
    painter->restore();
}
