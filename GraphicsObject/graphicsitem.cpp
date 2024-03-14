#include "graphicsitem.h"
#include "graphicsitemgroup.h"
#include "NodeBase.h"
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

void GraphicsItem::setPos(const QPointF &pos)
{
    setPos(pos.x(), pos.y());
}

void GraphicsItem::setPos(qreal x, qreal y)
{
    m_subItem->setPos(x, y);

    if (m_AtrributeNode->getAttribute(X)->getValue().toDouble() != m_subItem->scenePos().x()) {
        m_AtrributeNode->getAttribute(X)->setValue(m_subItem->scenePos().x());
    }

    if (m_AtrributeNode->getAttribute(Y)->getValue().toDouble() != m_subItem->scenePos().y()) {
        m_AtrributeNode->getAttribute(Y)->setValue(m_subItem->scenePos().y());
    }
}

QPointF GraphicsItem::pos() const
{
    return m_subItem->pos();
}

qreal GraphicsItem::initAngle() const
{
    return m_initAngle;
}

void GraphicsItem::setInitAngle(qreal newInitAngle)
{
    m_initAngle = newInitAngle;
}

void GraphicsItem::setChildItemRotation(GraphicsItem *item, qreal angleGroup)
{
    item->setGroupAngle(angleGroup);
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        foreach (auto childItem, itemGroup->getChildItems()) {
            setChildItemRotation(childItem, itemGroup->rotation() + itemGroup->groupAngle());
        }
    }
}

NodeBase *GraphicsItem::getCurrentNode() const
{
    return m_AtrributeNode;
}

void GraphicsItem::updateAttribute()
{
    QPointF pos = m_subItem->scenePos();
    if (m_AtrributeNode->getAttribute(X)->getValue().toDouble() != pos.x()) {
        m_AtrributeNode->getAttribute(X)->setValue(pos.x());
    }
    if (m_AtrributeNode->getAttribute(Y)->getValue().toDouble() != pos.y()) {
        m_AtrributeNode->getAttribute(Y)->setValue(pos.y());
    }

    if (m_AtrributeNode->getAttribute(WIDTH)->getValue().toDouble() != m_localRect.width()) {
        m_AtrributeNode->getAttribute(WIDTH)->setValue(m_localRect.width());
    }
    if (m_AtrributeNode->getAttribute(HEIGHT)->getValue().toDouble() != m_localRect.height()) {
        m_AtrributeNode->getAttribute(HEIGHT)->setValue(m_localRect.height());
    }
}

qreal GraphicsItem::zValue() const
{
    return m_zValue;
}

void GraphicsItem::setZValue(qreal newZValue)
{
    if (m_zValue == newZValue) return;

    m_zValue = newZValue;
    emit sendZValueChange();
}

//QGraphicsItemGroup *GraphicsItem::itemAncestor() const
//{
//    return m_itemAncestor;
//}

//void GraphicsItem::setItemAncestor(QGraphicsItemGroup *newItemAncestor)
//{
////    if (this->type() == GraphicsItemType::GroupItem) {
////        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(this);
////        foreach (auto childItem, itemGroup->getChildItems()) {
////            childItem->setItemAncestor(newItemAncestor);
////        }
////    }

//    m_itemAncestor = newItemAncestor;
//}

GraphicsItemGroup *GraphicsItem::itemGroup() const
{
    return m_itemGroup;
}

void GraphicsItem::setItemGroup(GraphicsItemGroup *newItemGroup)
{
    if (this->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(this);
        foreach (auto childItem, itemGroup->getChildItems()) {
            childItem->setItemGroup(newItemGroup);
        }
    }

    m_itemGroup = newItemGroup;
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

    if (m_AtrributeNode->getAttribute(ROTATE)->getValue().toDouble() != newAngle) {
        m_AtrributeNode->getAttribute(ROTATE)->setValue(newAngle);
    }
}

qreal GraphicsItem::rotation() const
{
    return m_rotationAngle;
}

void GraphicsItem::move(const QPointF &point)
{
    m_subItem->moveBy(point.x(), point.y());
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
    stretch(newWidth / m_localRect.width(), 1, m_localRect.topLeft());
    updateCoordinate();
}

qreal GraphicsItem::height() const
{
    return m_localRect.height();
}

void GraphicsItem::setHeight(qreal newHeight)
{
    stretch(1, newHeight / m_localRect.height(), m_localRect.topLeft());
    updateCoordinate();
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
//    qDebug () << "setScale m_scaleX:" << m_scaleX;
    stretch(scaleX, scaleY, QPointF(0, 0));
}

void GraphicsItem::onXPositionAttributeValueChanged(const QVariant& value)
{
    QPointF scenePos = m_subItem->scenePos();
    qreal x = value.toDouble();
    if (x == scenePos.x())
        return;

    scenePos.setX(x);
    m_subItem->setPos(m_subItem->mapFromScene(scenePos));
    emit sendUpdateHandle();
}

void GraphicsItem::onYPositionAttributeValueChanged(const QVariant& value)
{
    QPointF scenePos = m_subItem->scenePos();
    qreal y = value.toDouble();
    if (y == scenePos.y())
        return;

    scenePos.setY(y);
    m_subItem->setPos(m_subItem->mapFromScene(scenePos));
    emit sendUpdateHandle();
}

void GraphicsItem::onZPositionAttributeValueChanged(const QVariant& value)
{
    qreal itemZValue = value.toDouble();
    if (itemZValue == zValue())
        return;

    setZValue(value.toDouble());
    emit sendUpdateHandle();
}

void GraphicsItem::onWidthAttributeValueChanged(const QVariant& value)
{
    qreal itemWidth = value.toInt();
    if (itemWidth == width())
        return;

    setWidth(itemWidth);
    emit sendUpdateHandle();
}

void GraphicsItem::onHeightAttributeValueChanged(const QVariant& value)
{
    qreal itemHeight = value.toInt();
    if (itemHeight == height())
        return;

    setHeight(itemHeight);
    emit sendUpdateHandle();
}

void GraphicsItem::onRotateAttributeValueChanged(const QVariant& value)
{
    qreal roatateAngle = value.toDouble();
    if (roatateAngle == rotation())
        return;

    setRotation(roatateAngle);
    emit sendUpdateHandle();
}
