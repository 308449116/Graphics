#include "graphicshandle.h"
#include "graphicsitem.h"

#include <QStyleOptionGraphicsItem>
#include <QPainter>

GraphicsHandle::GraphicsHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,m_handleType(handleType)
    ,m_state(HandleOff)
    ,m_borderColor(Qt::white)
    ,m_selection(selection)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
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

    //高亮选中
    if (option->state & QStyle::State_Selected) {
        //        qt_graphicsItem_highlightSelected(this, painter, option);
    }
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
    m_borderColor = Qt::white;
    m_state = st;
}

void GraphicsHandle::setLocalRect(QRectF localRect)
{
    m_localRect = localRect;
}

void GraphicsHandle::setItem(GraphicsItem *item)
{
//    if (item) {
//        connect(item, &GraphicsItem::selectedChange, [this](GraphicsItem *item, bool checked) {
//            setVisible(checked);
//        });
//    }

    m_item = item;
}

void GraphicsHandle::move(qreal x, qreal y)
{
    setPos(x,y);
}

QRectF GraphicsHandle::boundingRect() const
{
    return m_localRect;
}









