#ifndef GRAPHICSSIZEHANDLE_H
#define GRAPHICSSIZEHANDLE_H

#include "graphicshandle.h"

class QGraphicsSceneMouseEvent;
class GraphicsSelection;
const static int GRAPHICS_HANDLE_SIZE = 6;

class GraphicsSizeHandle : public GraphicsHandle
{
public:
    GraphicsSizeHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);
//    QRectF boundingRect() const override;

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
//    QPointF m_pressedScenePos;
//    QPointF m_lastScenePos;
//    QPointF m_initialPos;
    QPointF m_oppositePos;
};

#endif // GRAPHICSSIZEHANDLE_H
