#include "graphicsitem.h"
#include "graphicsitemgroup.h"
#include "attributemodel/nodebase.h"
#include "utils/attribute_constants.h"
#include "utils/uid.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

using namespace Utils::Constants;

GraphicsItem::GraphicsItem(QObject *parent)
    : QObject(parent), m_uid(Utils::Uid::CreateStringUid())
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

void GraphicsItem::setUid(const QString &uid)
{
    m_uid = uid;
    m_AtrributeNode->getAttribute(QString::fromUtf8(ID))->setValue(m_uid);
}

void GraphicsItem::setPos(const QPointF &pos)
{
    setPos(pos.x(), pos.y());
}

void GraphicsItem::setPos(qreal x, qreal y)
{
    m_subItem->setPos(x, y);
    updateXYAttribute();

    if (this->itemGroup()) {
        emit sendGraphicsItemChanged();
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
        for (auto childItem : itemGroup->getChildItems()) {
            setChildItemRotation(childItem, itemGroup->rotation() + itemGroup->groupAngle());
        }
    }
}

NodeBase *GraphicsItem::getCurrentNode() const
{
    return m_AtrributeNode;
}

void GraphicsItem::updateBaseAttribute()
{
    if (m_AtrributeNode == nullptr) {
        return;
    }

    updateXYAttribute();
    m_AtrributeNode->getAttribute(QString::fromUtf8(WIDTH))->setValue(m_localRect.width());
    m_AtrributeNode->getAttribute(QString::fromUtf8(HEIGHT))->setValue(m_localRect.height());
    m_AtrributeNode->getAttribute(QString::fromUtf8(ROTATE))->setValue(m_rotationAngle);
    m_AtrributeNode->getAttribute(QString::fromUtf8(ITEMNAME))->setValue(m_itemName);
}

void GraphicsItem::updateXYAttribute()
{
    if (m_AtrributeNode == nullptr) {
        return;
    }

    QPointF topLeft = m_subItem->mapRectToScene(this->getRect()).topLeft();
//    QPointF topLeft = m_subItem->sceneBoundingRect().topLeft();
//    qDebug() << "========== topLeft:" << topLeft;
//    qDebug() << "========== mapRectToScene:" << m_subItem->mapRectToScene(this->getRect());
//    if (topLeft.x() < 0) {
//        m_subItem->moveBy(-topLeft.x(), 0);
//        topLeft.setX(0);
//    }
//    if (topLeft.y() < 0) {
//        m_subItem->moveBy(0, -topLeft.y());
//        topLeft.setY(0);
//    }

    m_AtrributeNode->getAttribute(QString::fromUtf8(X))->setValue(topLeft.x());
    m_AtrributeNode->getAttribute(QString::fromUtf8(Y))->setValue(topLeft.y());
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
    emit sendZValueChanged();
//    m_AtrributeNode->getAttribute(QString::fromUtf8(Z))->setValue(m_zValue);
}

void GraphicsItem::writeBaseAttributes(QXmlStreamWriter *xml)
{
    xml->writeAttribute(POSX, QString("%1").arg(m_subItem->pos().x()));
    xml->writeAttribute(POSY, QString("%1").arg(m_subItem->pos().y()));
}

void GraphicsItem::readBaseAttributes(QXmlStreamReader *xml)
{
    qreal posx = xml->attributes().value(POSX).toDouble();
    qreal posy = xml->attributes().value(POSY).toDouble();
    this->setPos(posx, posy);
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
        for (auto childItem : itemGroup->getChildItems()) {
            childItem->setItemGroup(newItemGroup);
        }
    }

    m_itemGroup = newItemGroup;
}

void GraphicsItem::setRotation(qreal newAngle, bool isSendChanged)
{
//    if (m_rotationAngle == newAngle) return;

    m_rotationAngle = newAngle;
    if (this->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(this);
        for (auto childItem : itemGroup->getChildItems()) {
            setChildItemRotation(childItem, m_rotationAngle + itemGroup->groupAngle());
        }
    }

    m_subItem->setRotation(newAngle);
    m_AtrributeNode->getAttribute(QString::fromUtf8(ROTATE))->setValue(m_rotationAngle);
    updateXYAttribute();

    if (this->itemGroup() && isSendChanged) {
        emit sendGraphicsItemChanged();
    }
}

qreal GraphicsItem::rotation() const
{
    return m_rotationAngle;
}

void GraphicsItem::moveBy(const QPointF &point)
{
    this->moveBy(point.x(), point.y());
}

void GraphicsItem::moveBy(qreal x, qreal y)
{
    m_subItem->moveBy(x, y);

    if (this->itemGroup()) {
        emit sendGraphicsItemChanged();
    }
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

    if (this->itemGroup()) {
        emit sendGraphicsItemChanged();
    }
}

qreal GraphicsItem::height() const
{
    return m_localRect.height();
}

void GraphicsItem::setHeight(qreal newHeight)
{
    stretch(1, newHeight / m_localRect.height(), m_localRect.topLeft());
    updateCoordinate();

    if (this->itemGroup()) {
        emit sendGraphicsItemChanged();
    }
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
    stretch(scaleX, scaleY, QPointF(0, 0));
}

void GraphicsItem::onXPositionAttributeValueChanged(const QVariant& value)
{
    if (m_AtrributeNode == nullptr ||
        value.toDouble() == m_subItem->mapRectToScene(this->getRect()).topLeft().x()) {
        return;
    }

    qreal offset = m_AtrributeNode->getAttribute(QString::fromUtf8(X))->getValue().toDouble() -
                   m_AtrributeNode->getAttribute(QString::fromUtf8(X))->getLastValue().toDouble();
    this->moveBy(offset, 0);
    emit sendUpdateHandle();
}

void GraphicsItem::onYPositionAttributeValueChanged(const QVariant& value)
{
    if (m_AtrributeNode == nullptr ||
        value.toDouble() == m_subItem->mapRectToScene(this->getRect()).topLeft().y()) {
        return;
    }

    qreal offset = m_AtrributeNode->getAttribute(QString::fromUtf8(Y))->getValue().toDouble() -
                   m_AtrributeNode->getAttribute(QString::fromUtf8(Y))->getLastValue().toDouble();
    this->moveBy(0, offset);
    emit sendUpdateHandle();
}

//void GraphicsItem::onZPositionAttributeValueChanged(const QVariant& value)
//{
//    qreal itemZValue = value.toDouble();
//    if (itemZValue == zValue()) {
//        return;
//    }

//    setZValue(value.toDouble());
//    emit sendUpdateHandle();
//}

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

void GraphicsItem::onNameAttributeValueChanged(const QVariant& value)
{
    QString name = value.toString();
    if (name == itemName()) {
        return;
    }

    setItemName(name);
}

void GraphicsItem::onIDAttributeValueChanged(const QVariant &value)
{
    QString uidString = value.toString();
    if (uidString == uid()) {
        return;
    }

    setUid(uidString);
}

