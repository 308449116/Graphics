#include "abstractgraphicstemplate.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

template<typename BaseType>
AbstractGraphicsTemplate<BaseType>::AbstractGraphicsTemplate(QGraphicsItem *parent)
    : BaseType(parent)
{

}

template<typename BaseType>
QRectF AbstractGraphicsTemplate<BaseType>::getRect() const
{
    return m_localRect;
}

template<typename BaseType>
QGraphicsItem *AbstractGraphicsTemplate<BaseType>::duplicate() const
{
    return nullptr;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::updateCoordinate()
{

}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::move(const QPointF &point)
{
    Q_UNUSED(point);
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    Q_UNUSED(sx);
    Q_UNUSED(sy);
    Q_UNUSED(origin);
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::rotate(QPointF rotatePos, QPointF lastPos)
{
    Q_UNUSED(rotatePos);
    Q_UNUSED(lastPos);
}

template<typename BaseType>
qreal AbstractGraphicsTemplate<BaseType>::width() const
{
    return m_width;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setWidth(qreal width)
{
    m_width = width;
}

template<typename BaseType>
qreal AbstractGraphicsTemplate<BaseType>::height() const
{
    return m_height;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setHeight(qreal height)
{
    m_height = height;
}

template<typename BaseType>
QColor AbstractGraphicsTemplate<BaseType>::brushColor() const
{
    return m_brush.color();
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setBrushColor(const QColor &color)
{
    m_brush.setColor(color);
}

template<typename BaseType>
QBrush AbstractGraphicsTemplate<BaseType>::brush() const
{
    return m_brush;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setBrush(const QBrush &brush)
{
    m_brush = brush;
}

template<typename BaseType>
QPen AbstractGraphicsTemplate<BaseType>::pen() const
{
    return m_pen;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setPen(const QPen &pen)
{
    m_pen = pen;
}

template<typename BaseType>
QColor AbstractGraphicsTemplate<BaseType>::penColor() const
{
    return m_pen.color();

}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::qt_graphicsItem_highlightSelected(
    QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(getRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth;
    switch (item->type()) {
    case QGraphicsEllipseItem::Type:
        itemPenWidth = static_cast<QGraphicsEllipseItem *>(item)->pen().widthF();
        break;
    case QGraphicsPathItem::Type:
        itemPenWidth = static_cast<QGraphicsPathItem *>(item)->pen().widthF();
        break;
    case QGraphicsPolygonItem::Type:
        itemPenWidth = static_cast<QGraphicsPolygonItem *>(item)->pen().widthF();
        break;
    case QGraphicsRectItem::Type:
        itemPenWidth = static_cast<QGraphicsRectItem *>(item)->pen().widthF();
        break;
    case QGraphicsSimpleTextItem::Type:
        itemPenWidth = static_cast<QGraphicsSimpleTextItem *>(item)->pen().widthF();
        break;
    case QGraphicsLineItem::Type:
        itemPenWidth = static_cast<QGraphicsLineItem *>(item)->pen().widthF();
        break;
    default:
        itemPenWidth = 1.0;
    }
    const qreal pad = itemPenWidth / 2;

    const qreal penWidth = 0; // cosmetic pen

    const QColor fgcolor = option->palette.windowText().color();
    const QColor bgcolor( // ensure good contrast against fgcolor
        fgcolor.red()   > 127 ? 0 : 255,
        fgcolor.green() > 127 ? 0 : 255,
        fgcolor.blue()  > 127 ? 0 : 255);


    painter->setPen(QPen(bgcolor, penWidth, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(getRect().adjusted(-pad, -pad, pad, pad));

    painter->setPen(QPen(QColor("lightskyblue"), 0, Qt::SolidLine));
//    painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(getRect().adjusted(-pad, -pad, pad, pad));
}

template class AbstractGraphicsTemplate<QGraphicsItem>;
