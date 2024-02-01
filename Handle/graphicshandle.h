#ifndef GRAPHICSHANDLE_H
#define GRAPHICSHANDLE_H

#include <QGraphicsItem>
#include "graphicsitem.h"

class GraphicsSelection;

class GraphicsHandle : public QGraphicsItem
{
public:
    enum GraphicsHandleState {
        HandleOff = 0,
        HandleActive
    };

    enum HandleType {
        Handle_None = 0,
        Drag,
        LeftTop,
        Top,
        RightTop,
        Right,
        RightBottom,
        Bottom,
        LeftBottom,
        Left,
        Rotate,
        Line,
        HandleTypeEnd //必须以此类型结尾，增加类型只能从中间插入
    };

    GraphicsHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);

//    virtual void updateHandle(GraphicsItem *item);

    QRectF boundingRect() const override;

    GraphicsItem *item() const;

    int handleType() const;

    void setState(GraphicsHandleState st);

    GraphicsHandleState getState();

    void setLocalRect(QRectF localRect);

    void setItem(GraphicsItem *item);

    void move(qreal x, qreal y);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    const int m_handleType;
    QColor m_borderColor;
    QRectF m_localRect;
    QPointF m_pressedPos;
    QPointF m_lastPos;

    GraphicsHandleState m_state;
    GraphicsItem *m_item = nullptr;
    GraphicsSelection *m_selection = nullptr;
};

#endif // GRAPHICSHANDLE_H

