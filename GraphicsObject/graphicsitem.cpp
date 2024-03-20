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
    updateAttribute();
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
    if (m_AtrributeNode == nullptr) {
        return;
    }

    QPointF topLeft = m_subItem->sceneBoundingRect().topLeft();
    if (topLeft.x() < 0) {
        m_subItem->moveBy(-topLeft.x(), 0);
        topLeft.setX(0);
    }
    if (topLeft.y() < 0) {
        m_subItem->moveBy(0, -topLeft.y());
        topLeft.setY(0);
    }

    m_AtrributeNode->getAttribute(X)->setValue(topLeft.x());
    m_AtrributeNode->getAttribute(Y)->setValue(topLeft.y());
    m_AtrributeNode->getAttribute(Z)->setValue(m_zValue);
    m_AtrributeNode->getAttribute(WIDTH)->setValue(m_localRect.width());
    m_AtrributeNode->getAttribute(HEIGHT)->setValue(m_localRect.height());
    m_AtrributeNode->getAttribute(ROTATE)->setValue(m_rotationAngle);

//    if (m_AtrributeNode->getAttribute(X)->getValue().toDouble() != topLeft.x()) {
//        m_AtrributeNode->getAttribute(X)->setValue(topLeft.x());
//    }
//    if (m_AtrributeNode->getAttribute(Y)->getValue().toDouble() != topLeft.y()) {
//        m_AtrributeNode->getAttribute(Y)->setValue(topLeft.y());
//    }

//    if (m_AtrributeNode->getAttribute(Z)->getValue().toDouble() != m_zValue) {
//        m_AtrributeNode->getAttribute(Z)->setValue(m_zValue);
//    }

//    if (m_AtrributeNode->getAttribute(WIDTH)->getValue().toDouble() != m_localRect.width()) {
//        m_AtrributeNode->getAttribute(WIDTH)->setValue(m_localRect.width());
//    }
//    if (m_AtrributeNode->getAttribute(HEIGHT)->getValue().toDouble() != m_localRect.height()) {
//        m_AtrributeNode->getAttribute(HEIGHT)->setValue(m_localRect.height());
//    }

//    if (m_AtrributeNode->getAttribute(ROTATE)->getValue().toDouble() != m_rotationAngle) {
//        m_AtrributeNode->getAttribute(ROTATE)->setValue(m_rotationAngle);
//    }
}

qreal GraphicsItem::zValue() const
{
    return m_zValue;
}

void GraphicsItem::setZValue(qreal newZValue)
{
    if (m_zValue == newZValue) {
        return;
    }

    m_zValue = newZValue;
    emit sendZValueChange();
    updateAttribute();
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

    updateAttribute();
//    if (m_AtrributeNode->getAttribute(ROTATE)->getValue().toDouble() != newAngle) {
//        m_AtrributeNode->getAttribute(ROTATE)->setValue(newAngle);
//    }
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
    if (m_AtrributeNode == nullptr ||
        value.toDouble() == m_subItem->sceneBoundingRect().topLeft().x()) {
        return;
    }

    qreal offset = m_AtrributeNode->getAttribute(X)->getValue().toDouble() -
                   m_AtrributeNode->getAttribute(X)->getLastValue().toDouble();
    m_subItem->moveBy(offset, 0);
    emit sendUpdateHandle();
}

void GraphicsItem::onYPositionAttributeValueChanged(const QVariant& value)
{
    if (m_AtrributeNode == nullptr ||
        value.toDouble() == m_subItem->sceneBoundingRect().topLeft().y()) {
        return;
    }

    qreal offset = m_AtrributeNode->getAttribute(Y)->getValue().toDouble() -
                   m_AtrributeNode->getAttribute(Y)->getLastValue().toDouble();
    m_subItem->moveBy(0, offset);
    emit sendUpdateHandle();
}

void GraphicsItem::onZPositionAttributeValueChanged(const QVariant& value)
{
    qreal itemZValue = value.toDouble();
    if (itemZValue == zValue()) {
        return;
    }

    setZValue(value.toDouble());
    emit sendUpdateHandle();
}

void GraphicsItem::onWidthAttributeValueChanged(const QVariant& value)
{
    qreal itemWidth = value.toDouble();
    if (itemWidth == width()) {
        return;
    }

    setWidth(itemWidth);
    emit sendUpdateHandle();
}

void GraphicsItem::onHeightAttributeValueChanged(const QVariant& value)
{
    qreal itemHeight = value.toDouble();
    if (itemHeight == height()) {
        return;
    }

    setHeight(itemHeight);
    emit sendUpdateHandle();
}

void GraphicsItem::onRotateAttributeValueChanged(const QVariant& value)
{
    qreal roatateAngle = value.toDouble();
    if (roatateAngle == rotation()) {
        return;
    }

    setRotation(roatateAngle);
    emit sendUpdateHandle();
}
