#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include "graphicsitem.h"

class GraphicsRectItem : public GraphicsItem
{
public:
    explicit GraphicsRectItem(const QRectF &rect, QObject *parent = nullptr);
    void stretch(qreal sx , qreal sy , const QPointF &origin) override;
    void updateCoordinate() override;
    QSharedPointer<GraphicsItem> duplicate() const override;
    int type() const override;

private:
//    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QGraphicsRectItem *m_rectItem = nullptr;
    QPointF m_originPoint;
    QPointF m_oppositePos;
};

#endif // GRAPHICSRECTITEM_H
