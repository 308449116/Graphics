#include "graphicsitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : AbstractGraphicsTemplate<QGraphicsItem>(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

int GraphicsItem::type() const
{
    return Type;
}

QRectF GraphicsItem::boundingRect() const
{
    return m_localRect;
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // 自定义绘制
    customPaint(painter, option, widget);

    //高亮选中
    if (option->state & QStyle::State_Selected) {
        emit selectedChange(this, true);
        qt_graphicsItem_highlightSelected(this, painter, option);
    } else {
        emit selectedChange(this, false);
    }

}
