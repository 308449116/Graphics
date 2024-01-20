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
    m_angle = newAngle;
    setTransform();
}

qreal GraphicsItem::rotation()
{
    return m_angle;
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

qreal GraphicsItem::scaleX() const
{
    return m_scaleX;
}

void GraphicsItem::setScaleX(qreal newScaleX)
{
    m_scaleX = newScaleX;
    setTransform();
}

qreal GraphicsItem::scaleY() const
{
    return m_scaleY;
}

void GraphicsItem::setScaleY(qreal newScaleY)
{
    m_scaleY = newScaleY;
    setTransform();
}

void GraphicsItem::setTransform()
{
    QTransform transform;
    transform.translate(m_originPos.x(), m_originPos.y());
    transform.rotate(m_angle);
    transform.scale(m_scaleX, m_scaleY);
    transform.translate(-m_originPos.x(), -m_originPos.y());
    m_item->setTransform(transform);
}

QPointF GraphicsItem::originPos() const
{
    return m_originPos;
}

void GraphicsItem::setOriginPos(QPointF newOriginPos)
{
    m_originPos = newOriginPos;
}
