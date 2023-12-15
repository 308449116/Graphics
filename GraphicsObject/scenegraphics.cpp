#include "scenegraphics.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QApplication>

SceneGraphics::SceneGraphics(QObject* parent)
    : QGraphicsScene{parent}
{
    
}

//void SceneGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
    
//}

//void SceneGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
    
//}

//void SceneGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
    
//}

//void SceneGraphics::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
    
//}

void SceneGraphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete: {
        foreach (QGraphicsItem *item, selectedItems()) {
            emit deleteGraphicsItem(item);
            removeItem(item);
            delete item;
        }
//        deselectItems();
        break;
    }
    case Qt::Key_A: {
        if(QApplication::keyboardModifiers() & Qt::ControlModifier){
            foreach (QGraphicsItem *item, items()) {
                item->setSelected(true);
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

void SceneGraphics::mouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch( mouseEvent->type() ) {
    case QEvent::GraphicsSceneMousePress:
        QGraphicsScene::mousePressEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseMove:
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseRelease:
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        break;
    default: break;
    }
}
