#ifndef GRAPHICSROTATEHANDLE_H
#define GRAPHICSROTATEHANDLE_H

#include "graphicshandle.h"

class QGraphicsSceneMouseEvent;
class GraphicsSelection;

class GraphicsRotateHandle : public GraphicsHandle
{
    Q_OBJECT
public:
    GraphicsRotateHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal m_lastAngle;
    qreal m_currentAngle;
    int m_rotateIconWidth = 20;
    int m_lineLen = 20;
    QPixmap m_rotatePixmap;
};

#endif // GRAPHICSROTATEHANDLE_H
