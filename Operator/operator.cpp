#include "operator.h"
#include "viewgraphics.h"
#include "Handle/graphicshandle.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>
#define PI 3.1416

Operator::Operator()
{
//    dashRect = 0;
//    selLayer = 0;
    m_oppositePos = QPointF();
    m_m_handleType = GraphicsHandle::Handle_None;
    m_selectMode = NONE;
}

void Operator::mousePressEvent(QGraphicsSceneMouseEvent *event, ViewGraphics *view)
{
    int m_handleType = GraphicsHandle::Handle_None;
    m_lastPos = m_pressedPos = event->scenePos();
    QGraphicsScene *scene = view->scene();
    if ( event->button() != Qt::LeftButton ) return;

//    if (!m_hoverSizer)
//       scene->mouseEvent(event);

    QList<QGraphicsItem *> items = scene->selectedItems();
    QGraphicsItem *item = nullptr;

    if ( items.count() == 1 )
        item = items.first();

    if ( item != 0 ) {
        m_handleType = view->collidesWithHandle(item, event->scenePos());
        if ( m_handleType != GraphicsHandle::Handle_None && m_handleType <= GraphicsHandle::Left ) {
            m_selectMode = SIZE;
        } else if (m_handleType != GraphicsHandle::Rotate) {
            m_selectMode =  ROTATE;
        } else {
            m_selectMode =  MOVE;
        }

        if ( m_handleType != GraphicsHandle::Handle_None && m_handleType <= GraphicsHandle::Left ) {
            m_oppositePos = view->opposite(item, m_handleType);
            if( m_oppositePos.x() == 0 )
                m_oppositePos.setX(1);
            if (m_oppositePos.y() == 0 )
                m_oppositePos.setY(1);
        }
    } else if ( items.count() > 1 ) {
        m_selectMode =  MOVE;
    }

    if( m_selectMode == NONE ) {
        //发送信号通知view，清空选中状态
    }

    if ( m_selectMode == MOVE && items.count() == 1 ) {
//        if (dashRect ){
//            scene->reMOVEItem(dashRect);
//            delete dashRect;
//            dashRect = 0;
//        }

//        dashRect = new QGraphicsPathItem(item->shape());
//        dashRect->setPen(Qt::DashLine);
//        dashRect->setPos(item->pos());
//        dashRect->setTransformOriginPoint(item->transformOriginPoint());
//        dashRect->setTransform(item->transform());
//        dashRect->setRotation(item->rotation());
//        dashRect->setScale(item->scale());
//        dashRect->setZValue(item->zValue());
//        scene->addItem(dashRect);

        m_initialPos = item->pos();
    }
}

void Operator::mouseMoveEvent(QGraphicsSceneMouseEvent *event, ViewGraphics *view)
{
    m_lastPos = event->scenePos();
    QGraphicsScene *scene = view->scene();
    QList<QGraphicsItem *> items = scene->selectedItems();
    QGraphicsItem * item = 0;
    if ( items.count() == 1 ) {
        item = items.first();
        if ( item != 0 ){
            if ( m_handleType != GraphicsHandle::Handle_None && m_selectMode == SIZE ){
                if (m_oppositePos.isNull()){
                    m_oppositePos = view->opposite(item, m_handleType);
                    if( m_oppositePos.x() == 0 )
                        m_oppositePos.setX(1);
                    if (m_oppositePos.y() == 0 )
                        m_oppositePos.setY(1);
                }

                QPointF new_delta = m_lastPos - m_oppositePos;
                QPointF initial_delta = m_pressedPos - m_oppositePos;

                double sx = new_delta.x() / initial_delta.x();
                double sy = new_delta.y() / initial_delta.y();

                item->stretch(m_handleType, sx , sy , m_oppositePos);

                emit scene->itemResize(item,m_handleType,QPointF(sx,sy));

              //  qDebug()<<"scale:"<<m_handleType<< item->mapToScene(m_oppositePos)<< sx << " ，" << sy
              //         << new_delta << item->mapFromScene(c_last)
              //         << initial_delta << item->mapFromScene(c_down) << item->boundingRect();

            } else if ( m_handleType > GraphicsHandle::Left  && m_selectMode == editor ){
                item->control(m_handleType,c_last);
                emit scene->itemControl(item,m_handleType,c_last,c_down);
            }
            else if(m_handleType == GraphicsHandle::Handle_None ){
                 int handle = item->collidesWithHandle(event->scenePos());
                 if ( handle != GraphicsHandle::Handle_None){
                     setCursor(scene,Qt::OpenHandCursor);
                     m_hoverSizer = true;
                 }else{
                     setCursor(scene,Qt::ArrowCursor);
                     m_hoverSizer = false;
                 }
             }
        }
    }

    if ( m_selectMode == MOVE ){
        setCursor(scene,Qt::ClosedHandCursor);
        if ( dashRect ){
            dashRect->setPos(m_initialPos + c_last - c_down);
        }
    }

    if ( m_selectMode != SIZE  && items.count() > 1)
    {
        scene->mouseEvent(event);

    }

}

void Operator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, ViewGraphics *view)
{

    Operator::mouseReleaseEvent(event,scene);

    if ( event->button() != Qt::LeftButton ) return;

    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ){
        AbstractShape * item = qgraphicsitem_cast<AbstractShape*>(items.first());
        if ( item != 0  && m_selectMode == MOVE && c_last != c_down ){
             item->setPos(m_initialPos + c_last - c_down);
             emit scene->itemMOVEd(item , c_last - c_down );
         }else if ( item !=0 && (m_selectMode == SIZE || m_selectMode ==editor) && c_last != c_down ){

            item->updateCoordinate();
        }
    }else if ( items.count() > 1 && m_selectMode == MOVE && c_last != c_down ){
          emit scene->itemMOVEd(NULL , c_last - c_down );
    }

    if (m_selectMode == netSelect ){

        if ( scene->view() ){
            QGraphicsView * view = scene->view();
            view->setDragMode(QGraphicsView::NoDrag);
        }
#if 0
        if ( scene->selectedItems().count() > 1 ){
            selLayer = scene->createGroup(scene->selectedItems());
            selLayer->setSelected(true);
        }
#endif
    }
    if (dashRect ){
        scene->reMOVEItem(dashRect);
        delete dashRect;
        dashRect = 0;
    }
    m_selectMode = none;
    m_handleType = GraphicsHandle::Handle_None;
    m_hoverSizer = false;
    m_oppositePos = QPointF();
    scene->mouseEvent(event);
}
