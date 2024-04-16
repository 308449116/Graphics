#include "scenegraphics.h"
#include "handle/graphicshandle.h"
#include "graphicsobject/graphicsitemgroup.h"
#include "attributemodel/canvasnode.h"
#include "attributemodel/nodebase.h"

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QPainter>

SceneGraphics::SceneGraphics(QObject* parent)
    : QGraphicsScene{parent}
{
    m_AtrributeNode = new CanvasNode(this);
}

SceneGraphics::~SceneGraphics()
{
    m_items.clear();
}

void SceneGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isControlModifier) {
        event->setModifiers(Qt::ControlModifier);
    }

    QGraphicsScene::mousePressEvent(event);
}

//void SceneGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
////    m_operator->mouseMoveEvent(event, this);
//    QGraphicsScene::mouseMoveEvent(event);
//}

void SceneGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isControlModifier) {
        event->setModifiers(Qt::ControlModifier);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void SceneGraphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete: {
        //        QList<GraphicsItem *> items;
        //        foreach (auto *item, selectedItems()) {
        //            GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
        //            if (handle && handle->handleType() == GraphicsHandle::Drag) {
        //                items.push_back(handle->item());
        //            }
        //        }

        //        if (!items.empty()) {
        //            emit deleteGraphicsItems(items);
        //        }
        //        deselectItems();
        emit deleteGraphicsItems();
        break;
    }
    case Qt::Key_A: {
        if(QApplication::keyboardModifiers() & Qt::ControlModifier){
            for (auto *item : items()) {
                GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
                if (handle && handle->handleType() == GraphicsHandle::Drag) {
                    handle->setSelected(true);
                }
            }
        }
        break;
    }
    default:
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void SceneGraphics::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

void SceneGraphics::removeItem(QGraphicsItem *item)
{
    QGraphicsScene::removeItem(item);
}

bool SceneGraphics::isControlModifier() const
{
    return m_isControlModifier;
}

void SceneGraphics::setIsControlModifier(bool newIsControlModifier)
{
    m_isControlModifier = newIsControlModifier;
}

void SceneGraphics::addItem(GraphicsItem *item)
{
    this->addItem(item->subItem());
    itemInsert(item);
//    qDebug() << "========= addItem m_items.count:" << m_items.count();
}

void SceneGraphics::removeItem(GraphicsItem *item)
{
    this->removeItem(item->subItem());
    itemRemove(item);
//    qDebug() << "========= removeItem m_items.count:" << m_items.count();
}

NodeBase *SceneGraphics::getCurrentNode()
{
    return m_AtrributeNode;
}

void SceneGraphics::drawBackground(QPainter *painter, const QRectF &rect)
{
    //    QPen pen;
    //    painter->setPen(pen);
    int left = int(rect.left()) - (int(rect.left()) % GRID_SIZE);
    int top = int(rect.top()) - (int(rect.top()) % GRID_SIZE);
    QVector<QPointF> points;
    for (int x = left; x < rect.right(); x += GRID_SIZE) {
        for (int y = top; y < rect.bottom(); y += GRID_SIZE) {
            points.append(QPointF(x, y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}

void SceneGraphics::itemInsert(GraphicsItem *item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        QSet<GraphicsItem *> itemSet = itemGroup->getChildItems();
        QSet<GraphicsItem *>::const_iterator it = itemSet.constBegin();
        for (; it != itemSet.constEnd(); it++) {
            itemInsert(*it);
        }
    }

    if (!m_items.contains(item)) {
        m_items.insert(item);
    }
}

void SceneGraphics::itemRemove(GraphicsItem *item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        QSet<GraphicsItem *> itemSet = itemGroup->getChildItems();
        QSet<GraphicsItem *>::const_iterator it = itemSet.constBegin();
        for (; it != itemSet.constEnd(); it++) {
            itemRemove(*it);
        }
    }

    if (m_items.contains(item)) {
        m_items.remove(item);
    }
}

//void SceneGraphics::mouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
//{
//    switch( mouseEvent->type() ) {
//    case QEvent::GraphicsSceneMousePress:
//        QGraphicsScene::mousePressEvent(mouseEvent);
//        break;
//    case QEvent::GraphicsSceneMouseMove:
//        QGraphicsScene::mouseMoveEvent(mouseEvent);
//        break;
//    case QEvent::GraphicsSceneMouseRelease:
//        QGraphicsScene::mouseReleaseEvent(mouseEvent);
//        break;
//    default: break;
//    }
//}

void SceneGraphics::onWidthAttributeValueChanged(const QVariant& value)
{
    qreal itemWidth = value.toDouble();
    if (itemWidth == width()) {
        return;
    }

    setSceneRect(0, 0, itemWidth, height());
}

void SceneGraphics::onHeightAttributeValueChanged(const QVariant& value)
{
    qreal itemHeight = value.toDouble();
    if (itemHeight == height()) {
        return;
    }

    setSceneRect(0, 0, width(), itemHeight);
}

QSet<GraphicsItem *> SceneGraphics::itemSet() const
{
    return m_items;
}

