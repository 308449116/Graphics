#ifndef GRAPHICSITEMGROUP_H
#define GRAPHICSITEMGROUP_H

#include <QGraphicsItemGroup>

#include "graphicsabstracttemplate.h"

class GraphicsItemGroup : public GraphicsAbstractTemplate<QGraphicsItemGroup>
{
public:
    explicit GraphicsItemGroup(QGraphicsItem *parent = nullptr);

    int  type() const override;

    QRectF boundingRect() const override;

    void updateCoordinate() override;

    QSharedPointer<GraphicsAbstractItem> duplicate() const override;

    void stretch(qreal sx, qreal sy, const QPointF &origin) override;
private:
    QList<QSharedPointer<GraphicsAbstractItem> > duplicateItems() const;

};

extern template class GraphicsAbstractTemplate<QGraphicsItemGroup>;

#endif // GRAPHICSITEMGROUP_H
