#include "operator.h"
#include "viewgraphics.h"
#include "scenegraphics.h"
#include "graphicsitem.h"
#include "graphicshandle.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>
#define PI 3.1416

Operator::Operator()
{
//    dashRect = 0;
//    selLayer = 0;
    m_oppositePos = QPointF();
    m_handleType = GraphicsHandle::Handle_None;
    m_selectMode = NONE;
    m_hideHandleSended = false;
    m_lastAngle = 0;
}

void Operator::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if (event->button() != Qt::LeftButton) return;

    if (scene->views().count() <= 0) return;
    ViewGraphics *view = dynamic_cast<ViewGraphics *>(scene->views().first());

    m_handleType = GraphicsHandle::Handle_None;
    m_lastScenePos = m_pressedScenePos = event->scenePos();
    m_pressedPos = event->pos();

//    dynamic_cast<SceneGraphics *>(scene)->mouseEvent(event);

    QList<QGraphicsItem *> items = scene->selectedItems();
    GraphicsItem *item = nullptr;

    if ( items.count() == 1 ) {
        item = qgraphicsitem_cast<GraphicsItem *>(items.first());
    }

    if ( item ) {
        m_handleType = view->collidesWithHandle(item, event->scenePos());
        qDebug() << "Operator mousePressEvent m_handleType:" << m_handleType;
        if ( m_handleType != GraphicsHandle::Handle_None && m_handleType <= GraphicsHandle::Left ) {
            m_selectMode = SIZE;
            m_oppositePos = view->opposite(item, m_handleType);
            qDebug() << "mousePressEvent m_handleType:" << m_handleType
                     << "  oppositePos:" << m_oppositePos;

            if( m_oppositePos.x() == 0 )
                m_oppositePos.setX(1);
            if (m_oppositePos.y() == 0 )
                m_oppositePos.setY(1);
//            m_oppositePos = item->mapFromScene(oppositePos);
        } else if (m_handleType == GraphicsHandle::Rotate) {
            QPointF origin = item->mapToScene(item->getRect().center());
            qreal len_y = m_lastScenePos.y() - origin.y();
            qreal len_x = m_lastScenePos.x() - origin.x();
            qreal angle = atan2(len_y, len_x) * 180 / PI;
            m_lastAngle = angle;
            m_selectMode =  ROTATE;
            m_currentAngle = item->rotation();
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
    m_lastScenePos = event->scenePos();
    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ) {
        GraphicsItem *item = qgraphicsitem_cast<GraphicsItem *>(items.first());
        if ( item != 0 ) {
            if (!m_hideHandleSended) {
                emit dynamic_cast<SceneGraphics *>(scene)->handleStateChange(item, true);
                m_hideHandleSended = true;
            }

            //拉伸处理
            if ( m_handleType != GraphicsHandle::Handle_None && m_selectMode == SIZE ) {
//                if (m_oppositePos.isNull()){
//                    m_oppositePos = view->opposite(item, m_handleType);
//                    if( m_oppositePos.x() == 0 )
//                        m_oppositePos.setX(1);
//                    if (m_oppositePos.y() == 0 )
//                        m_oppositePos.setY(1);
//                }
                qDebug() << "mouseMoveEvent m_handleType:" << m_handleType
                         << "  m_oppositePos:" << m_oppositePos;

                QPointF beginOffset = item->mapFromScene(m_pressedScenePos) - item->mapFromScene(m_oppositePos);
                QPointF endOffset = item->mapFromScene(m_lastScenePos) - item->mapFromScene(m_oppositePos);

                qreal sx = endOffset.x() / beginOffset.x();
                qreal sy = endOffset.y() / beginOffset.y();
                qDebug() << "1111 sx:" << sx <<" sy:" << sy;

                switch (m_handleType) {
                case GraphicsHandle::Right:
                case GraphicsHandle::Left:
                    sy = 1;
                    break;
                case GraphicsHandle::Top:
                case GraphicsHandle::Bottom:
                    sx = 1;
                    break;
//                case GraphicsHandle::LeftTop:
//                case GraphicsHandle::LeftBottom:
//                case GraphicsHandle::RightTop:
//                case GraphicsHandle::RightBottom:
//                    qDebug() << "item->getRatio:" << item->getRatio();
//                    sy = sx * item->getRatio();
//                    break;
                default:
                    break;
                }
                qDebug() << "2222 sx:" << sx <<" sy:" << sy;

                item->stretch(sx , sy , item->mapFromScene(m_oppositePos));

//                emit scene->itemResize(item,m_handleType,QPointF(sx,sy));
            } else if(m_handleType == GraphicsHandle::Rotate && m_selectMode == ROTATE) {
                //旋转处理
                qDebug() << "处理旋转开始...";
//                item->rotate(m_pressedScenePos, m_lastScenePos);
                QPointF origin = item->mapToScene(item->getRect().center());
//                item->setTransformOriginPoint(item->getRect().center());

                qreal len_y = m_lastScenePos.y() - origin.y();
                qreal len_x = m_lastScenePos.x() - origin.x();
                qreal angle = atan2(len_y, len_x) * 180 / PI;
                angle = m_currentAngle + int(angle - m_lastAngle) ;
                if ( angle > 360 )
                    angle -= 360;
                if ( angle < -360 )
                    angle+=360;

                item->setRotation( angle );
            } else if ( m_selectMode == MOVE ) {
                //移动处理
                item->setPos(m_initialPos + m_lastScenePos - m_pressedScenePos);
            }
        }
    }

//    if ( m_selectMode == MOVE ) {
//        item->setPos(m_initialPos + m_lastScenePos - m_pressedScenePos);
//    }

//    if ( m_selectMode != SIZE  && items.count() > 1) {
//        scene->mouseEvent(event);
//    }
}

void Operator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene)
{
    if ( event->button() != Qt::LeftButton ) return;
    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ) {
        GraphicsItem *item = qgraphicsitem_cast<GraphicsItem *>(items.first());
        if ( item && m_lastScenePos != m_pressedScenePos ) {
//            emit dynamic_cast<SceneGraphics *>(scene)->handleStateChange(item, false);
            m_hideHandleSended = false;
            if (m_selectMode == ROTATE) {
//                emit scene->itemRotate(item , m_lastScenePos - m_pressedScenePos);

            } else if (m_selectMode == SIZE) {
                item->updateCoordinate();
//                emit scene->itemResize(item , m_lastScenePos - m_pressedScenePos);
            } else {
//                emit scene->itemMove(item , m_lastScenePos - m_pressedScenePos);
            }
            emit dynamic_cast<SceneGraphics *>(scene)->updateItemHandle(item);
        }
    } else if ( items.count() > 1 && m_selectMode == MOVE && m_lastScenePos != m_pressedScenePos ){
//          emit scene->itemMove(NULL , m_lastScenePos - m_pressedScenePos );
    }

    m_selectMode = NONE;
    m_handleType = GraphicsHandle::Handle_None;
    m_oppositePos = QPointF();
    m_lastAngle = 0;
}

qreal Operator::CalculatingAngle(GraphicsItem *item, const QPointF &point)
{
    QPointF origin = item->mapToScene(item->getRect().center());

    qreal len_y = point.y() - origin.y();
    qreal len_x = point.x() - origin.x();
    qreal angle = atan2(len_y, len_x) * 180 / PI;

    angle = item->rotation() + int(angle - m_lastAngle) ;

    if ( angle > 360 )
        angle -= 360;
    if ( angle < -360 )
        angle+=360;

    return angle;
}
