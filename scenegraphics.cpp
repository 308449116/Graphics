#include "scenegraphics.h"
#include "graphicshandle.h"

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QPainter>

SceneGraphics::SceneGraphics(QObject* parent)
    : QGraphicsScene{parent}
{

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
            foreach (auto *item, items()) {
                GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
                if (handle && handle->handleType() == GraphicsHandle::Drag) {
                    handle->setSelected(true);
                }
            }
            //            if(selectedItems().length() == 1) signalSelectItem(selectedItems().at(0));
        }
        break;
    }
    default:
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void SceneGraphics::deselectItems()
{
    foreach (auto *item, selectedItems()) {
        removeItem(item);
        item->setSelected(false);
    }
}

int SceneGraphics::gridSize() const
{
    return m_gridSize;
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
    m_items.insert(item);
}

void SceneGraphics::removeItem(GraphicsItem *item)
{
    this->removeItem(item->subItem());
    m_items.remove(item);
}

void SceneGraphics::drawBackground(QPainter *painter, const QRectF &rect)
{
    //    QPen pen;
    //    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % m_gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % m_gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += m_gridSize) {
        for (qreal y = top; y < rect.bottom(); y += m_gridSize) {
            points.append(QPointF(x, y));
        }
    }
    painter->drawPoints(points.data(), points.size());
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
