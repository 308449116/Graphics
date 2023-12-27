#include "scenegraphics.h"
#include "graphicshandle.h"
#include "graphicsitem.h"
//#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QApplication>

SceneGraphics::SceneGraphics(QObject* parent)
    : QGraphicsScene{parent}
{
    
}

//void SceneGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsScene::mousePressEvent(event);
////    m_operator->mousePressEvent(event, this);
//}

//void SceneGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
////    m_operator->mouseMoveEvent(event, this);
//    QGraphicsScene::mouseMoveEvent(event);
//}

//void SceneGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
////    m_operator->mouseReleaseEvent(event, this);
//    QGraphicsScene::mouseReleaseEvent(event);
//}

void SceneGraphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete: {
        QList<GraphicsItem *> items;
        foreach (QGraphicsItem *item, selectedItems()) {
            GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
            if (handle && handle->handleType() == GraphicsHandle::Drag) {
                items << handle->item();
            }
        }

        if (!items.empty()) {
            emit deleteGraphicsItems(items);
        }
//        deselectItems();
        break;
    }
    case Qt::Key_A: {
        if(QApplication::keyboardModifiers() & Qt::ControlModifier){
            foreach (QGraphicsItem *item, items()) {
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
    foreach (QGraphicsItem *item, selectedItems()) {
        removeItem(item);
        item->setSelected(false);
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
