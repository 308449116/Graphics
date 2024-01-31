#ifndef GRAPHICSITEMGROUP_H
#define GRAPHICSITEMGROUP_H

#include <QGraphicsItemGroup>

#include "graphicsitem.h"

class GraphicsItemGroup : public GraphicsItem
{
    Q_OBJECT
public:
    explicit GraphicsItemGroup(QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);

    explicit GraphicsItemGroup(QList<QSharedPointer<GraphicsItem> > items, QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);

    virtual ~GraphicsItemGroup();

    int  type() const override;

    void updateCoordinate() override;

//    void setRotation(qreal newAngle)  override;

    QSharedPointer<GraphicsItem> duplicate() const override;

    void stretch(qreal sx, qreal sy, const QPointF &origin) override;

    QSet<QSharedPointer<GraphicsItem > > getChildItems() const;

    void addToGroup(QSharedPointer<GraphicsItem> item);

    void removeFromGroup(QSharedPointer<GraphicsItem> item);

protected:
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

private:
    QList<QSharedPointer<GraphicsItem> > duplicateItems() const;
    void updateItemAngle(QSharedPointer<GraphicsItem> item, qreal rotationAngel);
//    void setChildItemRotation(QSharedPointer<GraphicsItem> item);
//    void setItemZValue(QSharedPointer<GraphicsItem> item);

private:
    QGraphicsItemGroup *m_itemGroup = nullptr;
    QSet<QSharedPointer<GraphicsItem > > m_childItems;
//    qreal m_rotationAngle = 0;
    //    qreal m_lastAngle = 0;
};

//extern template class GraphicsAbstractTemplate<QGraphicsItem>;
//extern template class GraphicsAbstractTemplate<QGraphicsItemGroup>;

#endif // GRAPHICSITEMGROUP_H
