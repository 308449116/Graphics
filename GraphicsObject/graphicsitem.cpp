#include "graphicsitem.h"
#include "graphicsitemgroup.h"
#include "common.h"

GraphicsItem::GraphicsItem(QObject *parent)
    : QObject(parent)
{
}

GraphicsItem::~GraphicsItem()
{
    if (m_subItem) {
        delete m_subItem;
        m_subItem = nullptr;
    }
}

QRectF GraphicsItem::getRect() const
{
    return m_localRect;
}

qreal GraphicsItem::initAngle() const
{
    return m_initAngle;
}

void GraphicsItem::setInitAngle(qreal newInitAngle)
{
    m_initAngle = newInitAngle;
}

void GraphicsItem::setChildItemRotation(QSharedPointer<GraphicsItem> item, qreal angleGroup)
{
    item->setGroupAngle(angleGroup);
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item.data());
        foreach (auto childItem, itemGroup->getChildItems()) {
            setChildItemRotation(childItem, itemGroup->rotation() + itemGroup->groupAngle());
        }
    }
}

void GraphicsItem::setRotation(qreal newAngle)
{
    if (m_rotationAngle == newAngle) return;

    m_rotationAngle = newAngle;
    if (this->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(this);
        foreach (auto childItem, itemGroup->getChildItems()) {
            setChildItemRotation(childItem, m_rotationAngle + itemGroup->groupAngle());
        }
    }

    m_subItem->setRotation(newAngle);
}

qreal GraphicsItem::rotation() const
{
    return m_rotationAngle;
}

void GraphicsItem::move(const QPointF &point)
{
    m_subItem->moveBy(point.x(),point.y());
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
    return m_localRect.width();
}

void GraphicsItem::setWidth(qreal newWidth)
{
    m_scaleX = newWidth / m_localRect.width();
    stretch(m_scaleX, m_scaleY, QPointF(0, 0));
}

qreal GraphicsItem::height() const
{
    return m_localRect.height();
}

void GraphicsItem::setHeight(qreal newHeight)
{
    m_scaleY = newHeight / m_localRect.height();
    stretch(m_scaleX, m_scaleY, QPointF(0, 0));
}

QGraphicsItem *GraphicsItem::subItem() const
{
    return m_subItem;
}

QRectF GraphicsItem::boundingRect() const
{
    return m_subItem->boundingRect();
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
    qDebug () << "setScale m_scaleX:" << m_scaleX;
    stretch(scaleX, scaleY, QPointF(0, 0));
}

//QSharedPointer<GraphicsItem> GraphicsItem::itemParent() const
//{
//    return m_itemParent;
//}

//void GraphicsItem::setItemParent(QSharedPointer<GraphicsItem> newItemParent)
//{
//    m_itemParent = newItemParent;
//}
