#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include <QObject>
#include "graphicsitem.h"

class GraphicsRectItem : public GraphicsItem
{
public:
    explicit GraphicsRectItem(const QRectF &rect, GraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void stretch(qreal sx , qreal sy , const QPointF &origin) override;
    void updateCoordinate() override;
    void move(const QPointF &point) override;
    QGraphicsItem *duplicate () const override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF m_initialRect;
    QPointF m_originPoint;
};

#endif // GRAPHICSRECTITEM_H
