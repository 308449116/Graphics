#ifndef GRAPHICSDRAGHANDLE_H
#define GRAPHICSDRAGHANDLE_H

#include <QObject>
#include "graphicshandle.h"

class QGraphicsSceneMouseEvent;
class GraphicsSelection;

class GraphicsDragHandle : public GraphicsHandle
{
    Q_OBJECT
public:
    GraphicsDragHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

private:
    QPointF m_initialPos;
};

#endif // GRAPHICSDRAGHANDLE_H
