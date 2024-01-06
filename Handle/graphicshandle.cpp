#include "graphicshandle.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

GraphicsHandle::GraphicsHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    ,m_handleType(handleType)
    ,m_borderColor(Qt::white)
    ,m_state(GraphicsHandleState::HandleActive)
    ,m_selection(selection)
{
//    setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setZValue(1);
    hide();
}

int GraphicsHandle::handleType() const
{
    return m_handleType;
}


void GraphicsHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // 自定义绘制
    customPaint(painter, option, widget);
}

void GraphicsHandle::setState(GraphicsHandleState st)
{
    if (st == m_state)
        return;
//    switch (st) {
//    case HandleOff:
//        hide();
//        break;
//    case HandleActive:
//        show();
//        break;
//    }
//    m_borderColor = Qt::white;
    m_state = st;
}

GraphicsHandle::GraphicsHandleState GraphicsHandle::getState()
{
    return m_state;
}

void GraphicsHandle::setLocalRect(QRectF localRect)
{
    m_localRect = localRect;
}

void GraphicsHandle::setItem(QSharedPointer<GraphicsAbstractItem> item)
{
//    if (item) {
//        connect(item, &GraphicsItem::selectedChange, [this](GraphicsItem *item, bool checked) {
//            setVisible(checked);
//        });
//    }

    m_item = item;
}

QSharedPointer<GraphicsAbstractItem> GraphicsHandle::item() const
{
    return m_item;
}

void GraphicsHandle::move(qreal x, qreal y)
{
    setPos(x,y);
}

QRectF GraphicsHandle::boundingRect() const
{
    return m_localRect;
}









