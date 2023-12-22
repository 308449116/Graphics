#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QObject>
#include "abstractgraphicstemplate.h"

using AbstractGraphicsItem = AbstractGraphicsTemplate<QGraphicsItem>;

class GraphicsItem : public QObject,
                     public AbstractGraphicsTemplate<QGraphicsItem>
{
    Q_OBJECT
public:
    enum {
        Type = UserType + 1
    };

    explicit GraphicsItem(QGraphicsItem *parent = nullptr);
    virtual ~GraphicsItem() {}
    int  type() const override;
    QRectF boundingRect() const override;

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

extern template class AbstractGraphicsTemplate<QGraphicsItem>;
#endif // GRAPHICSITEM_H
