#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QObject>

#include "graphicsabstracttemplate.h"

class GraphicsItem : public GraphicsAbstractTemplate<QGraphicsItem>
{
public:
    explicit GraphicsItem(QGraphicsItem *parent = nullptr);

    virtual ~GraphicsItem() {}

    QRectF boundingRect() const override;

//    virtual QSharedPointer<GraphicsAbstractItem> duplicate() const = 0;

//    void setItemName(QString name);

//    QString getItemName() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

signals:
//    void selectedChange(GraphicsItem *item, bool checked);
//    void handleStateSwitch(bool isShow);

private:
    bool m_hideHandleSended = false;
};

extern template class GraphicsAbstractTemplate<QGraphicsItem>;

#endif // GRAPHICSITEM_H
