#ifndef GRAPHICSDRAGHANDLE_H
#define GRAPHICSDRAGHANDLE_H

#include "graphicshandle.h"

class ViewGraphics;
class GraphicsSelection;
class QGraphicsSceneMouseEvent;

class GraphicsDragHandle : public GraphicsHandle
{
public:
    GraphicsDragHandle(int handleType, ViewGraphics *view,
                       GraphicsSelection *selection, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
//    QPointF m_initialPos;
    ViewGraphics *m_view = nullptr;
    QHash<GraphicsItem *, QPointF> m_itemPosHash;
};

#endif // GRAPHICSDRAGHANDLE_H
