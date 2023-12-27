#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include "graphicsitem.h"

class GraphicsRectItem : public GraphicsItem
{
public:
    explicit GraphicsRectItem(const QRectF &rect, GraphicsItem *parent = nullptr);
    void move(const QPointF &point) override;
    void stretch(qreal sx , qreal sy , const QPointF &origin) override;
    void updateCoordinate() override;
    GraphicsItem *duplicate () const override;
    int  type() const override;

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPointF m_originPoint;
    QPointF m_oppositePos;
};

#endif // GRAPHICSRECTITEM_H
