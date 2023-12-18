#include "operator.h"
#include "viewgraphics.h"
#include "graphicsitem.h"
#include "graphicshandle.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>
//#define PI 3.1416

Operator::Operator()
{
//    dashRect = 0;
//    selLayer = 0;
    m_oppositePos = QPointF();
    m_handleType = GraphicsHandle::Handle_None;
    m_selectMode = NONE;
}

void Operator::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if (event->button() != Qt::LeftButton) return;

    if (scene->views().count() <= 0) return;
    ViewGraphics *view = dynamic_cast<ViewGraphics *>(scene->views().first());

    int m_handleType = GraphicsHandle::Handle_None;
    m_lastPos = m_pressedPos = event->scenePos();

//    if (!m_hoverSizer)
//       scene->mouseEvent(event);

    QList<QGraphicsItem *> items = scene->selectedItems();
    QGraphicsItem *item = nullptr;

    if ( items.count() == 1 )
        item = items.first();

    if ( item ) {
        m_handleType = view->collidesWithHandle(item, event->scenePos());
        if ( m_handleType != GraphicsHandle::Handle_None && m_handleType <= GraphicsHandle::Left ) {
            m_selectMode = SIZE;
            m_oppositePos = view->opposite(item, m_handleType);
            if( m_oppositePos.x() == 0 )
                m_oppositePos.setX(1);
            if (m_oppositePos.y() == 0 )
                m_oppositePos.setY(1);
        } else if (m_handleType != GraphicsHandle::Rotate) {
            m_selectMode =  ROTATE;
        } else {
            m_selectMode =  MOVE;
            m_initialPos = item->pos();

        }
    } else if ( items.count() > 1 ) {
        m_selectMode =  MOVE;
    }

    if( m_selectMode == NONE ) {
        //发送信号通知view，清空选中状态
    }

//    if ( m_selectMode == MOVE && items.count() == 1 ) {
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

//        m_initialPos = item->pos();
//    }
}

void Operator::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    m_lastPos = event->scenePos();
    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ) {
        AbstractGraphicsItem *item = qgraphicsitem_cast<AbstractGraphicsItem *>(items.first());
        if ( item != 0 ) {
            //拉伸处理
            if ( m_handleType != GraphicsHandle::Handle_None && m_selectMode == SIZE ) {
//                if (m_oppositePos.isNull()){
//                    m_oppositePos = view->opposite(item, m_handleType);
//                    if( m_oppositePos.x() == 0 )
//                        m_oppositePos.setX(1);
//                    if (m_oppositePos.y() == 0 )
//                        m_oppositePos.setY(1);
//                }

                QPointF beginOffset = m_pressedPos - m_oppositePos;
                QPointF endOffset = m_lastPos - m_oppositePos;

                double sx = endOffset.x() / beginOffset.x();
                double sy = endOffset.y() / beginOffset.y();

                item->stretch(sx , sy , m_oppositePos);

//                emit scene->itemResize(item,m_handleType,QPointF(sx,sy));
            } else if(m_handleType == GraphicsHandle::Rotate && m_selectMode == ROTATE) {
                //旋转处理
            } else if ( m_selectMode == MOVE ) {
                //移动处理
                item->setPos(m_initialPos + m_lastPos - m_pressedPos);
            }
        }
    }

//    if ( m_selectMode == MOVE ) {
//        item->setPos(m_initialPos + m_lastPos - m_pressedPos);
//    }

//    if ( m_selectMode != SIZE  && items.count() > 1) {
//        scene->mouseEvent(event);
//    }
}

void Operator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if ( event->button() != Qt::LeftButton ) return;
    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ){
        AbstractGraphicsItem *item = qgraphicsitem_cast<AbstractGraphicsItem *>(items.first());
        if ( item && m_lastPos != m_pressedPos ) {
            if (m_selectMode == ROTATE) {
//                emit scene->itemRotate(item , m_lastPos - m_pressedPos);
            } else if (m_selectMode == SIZE) {
//                item->updateCoordinate();
//                emit scene->itemResize(item , m_lastPos - m_pressedPos);
            } else {
//                emit scene->itemMove(item , m_lastPos - m_pressedPos);
            }
        }
    }else if ( items.count() > 1 && m_selectMode == MOVE && m_lastPos != m_pressedPos ){
//          emit scene->itemMove(NULL , m_lastPos - m_pressedPos );
    }

    m_selectMode = NONE;
    m_handleType = GraphicsHandle::Handle_None;
    m_oppositePos = QPointF();
}
