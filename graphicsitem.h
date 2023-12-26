#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QObject>
#include "graphicsabstracttemplate.h"

using GraphicsAbstractItem = GraphicsAbstractTemplate<QGraphicsItem>;

class GraphicsItem : public QObject,
                     public GraphicsAbstractItem
{
    Q_OBJECT
public:
    explicit GraphicsItem(QGraphicsItem *parent = nullptr);
    virtual ~GraphicsItem() {}
    QRectF boundingRect() const override;

    void setItemName(QString name);
    QString getItemName();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

signals:
    void selectedChange(GraphicsItem *item, bool checked);
//    void handleStateSwitch(bool isShow);

private:
    bool m_hideHandleSended = false;
};

extern template class GraphicsAbstractTemplate<QGraphicsItem>;
#endif // GRAPHICSITEM_H
