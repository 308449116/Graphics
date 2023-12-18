#include "graphicshandle.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPainter>

GraphicsHandle::GraphicsHandle(QGraphicsScene* scene , int handleType, bool control)
    :QGraphicsRectItem(-GRAPHICS_HANDLE_SIZE/2,
                       -GRAPHICS_HANDLE_SIZE/2,
                       GRAPHICS_HANDLE_SIZE,
                        GRAPHICS_HANDLE_SIZE)
    ,m_handleType(handleType)
    ,m_controlPoint(control)
    ,m_state(HandleOff)
    ,borderColor(Qt::white)
    , m_scene(scene)
{
//    this->setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    setZValue(1);
    scene->addItem(this);
    hide();
}


void GraphicsHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setPen(Qt::SolidLine);
    painter->setBrush(QBrush(borderColor));

    painter->setRenderHint(QPainter::Antialiasing,false);

    if ( m_controlPoint  )
    {
        painter->setPen(QPen(Qt::red,Qt::SolidLine));
        painter->setBrush(Qt::green);
        painter->drawEllipse(rect().center(),3,3);
    }
    else
    {
        painter->drawRect(rect());
    }
    painter->restore();
}


void GraphicsHandle::setState(GraphicsHandleState st)
{
    if (st == m_state)
        return;
    switch (st) {
    case HandleOff:
        hide();
        break;
    case HandleActive:
        show();
        break;
    }
    borderColor = Qt::white;
    m_state = st;
}

void GraphicsHandle::move(qreal x, qreal y)
{   
    setPos(x,y);
}

//void GraphicsHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
//{
//    borderColor = Qt::blue;
//    update();
//    QGraphicsRectItem::hoverEnterEvent(e);
//}

//void GraphicsHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
//{
//    borderColor = Qt::white;
//    update();
//    QGraphicsRectItem::hoverLeaveEvent(e);
//}







