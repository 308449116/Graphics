#ifndef GRAPHICSHANDLE_H
#define GRAPHICSHANDLE_H

#include <QGraphicsItem>

class GraphicsSelection;
class GraphicsItem;

class GraphicsHandle : public QGraphicsItem
{
public:
    enum GraphicsHandleState {
        HandleOff,
        HandleActive
    };

    enum HandleType {
        Handle_None = 0 ,
        LeftTop,
        Top,
        RightTop,
        Right,
        RightBottom,
        Bottom,
        LeftBottom,
        Left,
        Drag,
        Rotate,
        HandleTypeEnd //必须以此类型结尾，增加类型只能从中间插入
    };

    GraphicsHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);
    int handleType() const;
    GraphicsItem *item() const;
    QRectF boundingRect() const override;

    void setState(GraphicsHandleState st);
    void setLocalRect(QRectF localRect);
    void setItem(GraphicsItem *item);
    void move(qreal x, qreal y);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    const int m_handleType;
    GraphicsHandleState m_state;
    QColor m_borderColor;
    GraphicsItem *m_item;
    GraphicsSelection *m_selection;
    QRectF m_localRect;
    QPointF m_pressedScenePos;
    QPointF m_lastScenePos;
};


#endif // GRAPHICSHANDLE_H

