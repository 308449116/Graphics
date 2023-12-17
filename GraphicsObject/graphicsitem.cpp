#include "graphicsitem.h"

GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : AbstractGraphicsTemplate<QGraphicsItem>(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

int GraphicsItem::type() const
{
    return Type;
}
