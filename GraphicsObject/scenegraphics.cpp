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
//    Operator * tool = Operator::findTool( Operator::c_drawShape );
//    if ( tool )
//        tool->mousePressEvent(mouseEvent,this);
//}

//void SceneGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    Operator * tool = Operator::findTool( Operator::c_drawShape );
//    if ( tool )
//        tool->mouseMoveEvent(mouseEvent,this);
//}

//void SceneGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    Operator * tool = Operator::findTool( Operator::c_drawShape );
//    if ( tool )
//        tool->mouseReleaseEvent(mouseEvent,this);
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
