#ifndef GRAPHICSROTATEHANDLE_H
#define GRAPHICSROTATEHANDLE_H

#include "graphicshandle.h"

class ViewGraphics;
class GraphicsSelection;
class QGraphicsSceneMouseEvent;

class GraphicsRotateHandle : public GraphicsHandle
{
public:
    GraphicsRotateHandle(int handleType, ViewGraphics *view, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);

//    void updateHandle(GraphicsItem *item) override;

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal m_lastAngle = 0;
    qreal m_initAngle = 0;
    int m_rotateIconWidth = 20;
    int m_lineLen = 20;
    QPixmap m_rotatePixmap;
    ViewGraphics *m_view = nullptr;
};

#endif // GRAPHICSROTATEHANDLE_H
