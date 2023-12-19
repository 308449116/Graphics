#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include <QObject>
#include "graphicsitem.h"

class GraphicsRectItem : public GraphicsItem
{
public:
    explicit GraphicsRectItem(const QRectF &rect, GraphicsItem *parent = nullptr);
    void move(const QPointF &point) override;
    void stretch(qreal sx , qreal sy , const QPointF &origin) override;
    void rotate(QPointF rotatePos, QPointF lastPos) override;
    void updateCoordinate() override;
    GraphicsItem *duplicate () const override;

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF m_initialRect;
    QPointF m_originPoint;
};

#endif // GRAPHICSRECTITEM_H
