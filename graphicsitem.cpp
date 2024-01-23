#include "graphicsitem.h"

GraphicsItem::GraphicsItem(QObject *parent)
    : QObject(parent)
{
}

GraphicsItem::~GraphicsItem()
{
    if (m_item) {
        delete m_item;
        m_item = nullptr;
    }
}

QRectF GraphicsItem::getRect() const
{
    return m_localRect;
}

void GraphicsItem::addToGroup(QSharedPointer<GraphicsItem> item)
{
    Q_UNUSED(item);
}

void GraphicsItem::removeFromGroup(QSharedPointer<GraphicsItem> item)
{
    Q_UNUSED(item);
}

QSet<QSharedPointer<GraphicsItem> > GraphicsItem::getChildItems() const
{
    return QSet<QSharedPointer<GraphicsItem> >();
}

void GraphicsItem::setRotation(qreal newAngle)
{
    m_item->setRotation(newAngle);
}

qreal GraphicsItem::rotation()
{
    return m_item->rotation();
}

void GraphicsItem::move(const QPointF &point)
{
    m_item->moveBy(point.x(),point.y());
}

void GraphicsItem::setItemName(QString newName)
{
    m_itemName = newName;
}

QString GraphicsItem::itemName() const
{
    return m_itemName;
}

qreal GraphicsItem::width() const
{
    return m_width;
}

void GraphicsItem::setWidth(qreal newWidth)
{
    m_width = newWidth;
}

qreal GraphicsItem::height() const
{
    return m_height;
}

void GraphicsItem::setHeight(qreal newHeight)
{
    m_height = newHeight;
}

QGraphicsItem *GraphicsItem::item() const
{
    return m_item;
}

QRectF GraphicsItem::boundingRect() const
{
    return m_item->boundingRect();
}

bool GraphicsItem::contains(const QPointF &point) const
{
    return m_item->contains(point);
}

qreal GraphicsItem::groupAngle() const
{
    return m_groupAngle;
}

void GraphicsItem::setGroupAngle(qreal newGroupAngle)
{
    m_groupAngle = newGroupAngle;
}

QPointF GraphicsItem::oppositePos() const
{
    return m_oppositePos;
}

void GraphicsItem::setOppositePos(QPointF newOppositePos)
{
    m_oppositePos = newOppositePos;
}

qreal GraphicsItem::scaleY() const
{
    return m_scaleY;
}

qreal GraphicsItem::scaleX() const
{
    return m_scaleX;
}

void GraphicsItem::setScale(qreal scaleX, qreal scaleY)
{
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    stretch(scaleX, scaleY, QPointF(0, 0));
}
