#ifndef GRAPHICSITEMGROUP_H
#define GRAPHICSITEMGROUP_H

#include <QGraphicsItemGroup>

#include "graphicsabstracttemplate.h"

class GraphicsItemGroup : public GraphicsAbstractTemplate<QGraphicsItemGroup>
{
public:
    explicit GraphicsItemGroup(QGraphicsItem *parent = nullptr);

    explicit GraphicsItemGroup(QList<QSharedPointer<GraphicsAbstractItem> > items, QGraphicsItem *parent = nullptr);

    virtual ~GraphicsItemGroup();

    int  type() const override;

    QRectF boundingRect() const override;

    void updateCoordinate() override;

    void setRotation(qreal newAngle)  override;

    QSharedPointer<GraphicsAbstractItem> duplicate() const override;

    QSet<QSharedPointer<GraphicsAbstractItem > > getChildItems() const override;

    void stretch(qreal sx, qreal sy, const QPointF &origin) override;

    void addToGroup(QSharedPointer<GraphicsAbstractItem> item) override;

    void removeFromGroup(QSharedPointer<GraphicsAbstractItem> item) override;
protected:
//    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

private:
    QList<QSharedPointer<GraphicsAbstractItem> > duplicateItems() const;
    void setChildItemRotation(QSharedPointer<GraphicsAbstractItem> item);
    void addToGroup(QGraphicsItem *item);
    void removeFromGroup(QGraphicsItem *item);

private:
    QSet<QSharedPointer<GraphicsAbstractTemplate<QGraphicsItem> > > m_childItems;
    qreal m_currentAngle = 0;
    qreal m_lastAngle = 0;
};

extern template class GraphicsAbstractTemplate<QGraphicsItem>;
extern template class GraphicsAbstractTemplate<QGraphicsItemGroup>;

#endif // GRAPHICSITEMGROUP_H
