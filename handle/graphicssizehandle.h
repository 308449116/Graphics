#ifndef GRAPHICSSIZEHANDLE_H
#define GRAPHICSSIZEHANDLE_H

#include "graphicshandle.h"

class ViewGraphics;
class GraphicsSelection;
class QGraphicsSceneMouseEvent;

class GraphicsSizeHandle : public GraphicsHandle
{
public:
    GraphicsSizeHandle(int handleType, ViewGraphics *view, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);
//    QRectF boundingRect() const override;

//    void updateHandle(GraphicsItem *item) override;

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void setItemsOpposite(GraphicsItem *item);

private:
//    QPointF m_pressedScenePos;
//    QPointF m_lastScenePos;
//    QPointF m_initialPos;
    QPointF m_oppositePos;
    ViewGraphics *m_view = nullptr;
    qreal m_scaleX = 1.0;
    qreal m_scaleY = 1.0;
};

#endif // GRAPHICSSIZEHANDLE_H
