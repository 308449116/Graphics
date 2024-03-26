#ifndef GRAPHICSITEMGROUP_H
#define GRAPHICSITEMGROUP_H

#include <QGraphicsItemGroup>

#include "graphicsitem.h"

class GraphicsItemGroup : public GraphicsItem
{
    Q_OBJECT
public:
    explicit GraphicsItemGroup(QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);

    explicit GraphicsItemGroup(QList<GraphicsItem *> items, QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);

    virtual ~GraphicsItemGroup();

    int  type() const override;

    void updateCoordinate() override;

    bool loadFromXml(QXmlStreamReader *xml) override;

//    void setRotation(qreal newAngle)  override;

    GraphicsItem *duplicate() const override;

    void stretch(qreal sx, qreal sy, const QPointF &origin) override;

    QSet<GraphicsItem *> getChildItems() const;

    void addToGroup(GraphicsItem *item);

    void removeFromGroup(GraphicsItem *item);

protected:
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

private:
    void setChildItemZValue(GraphicsItem *item, int increment);
    QList<GraphicsItem *> duplicateItems() const;
    void updateItemAngle(GraphicsItem *item, qreal rotationAngel);
//    void setChildItemRotation(GraphicsItem *item);
//    void setItemZValue(GraphicsItem *item);

private:
    QGraphicsItemGroup *m_group = nullptr;
    QSet<GraphicsItem *> m_childItems;
//    qreal m_rotationAngle = 0;
//    qreal m_lastAngle = 0;
};

//extern template class GraphicsAbstractTemplate<QGraphicsItem>;
//extern template class GraphicsAbstractTemplate<QGraphicsItemGroup>;

#endif // GRAPHICSITEMGROUP_H
