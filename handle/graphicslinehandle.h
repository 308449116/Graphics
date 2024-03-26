#ifndef GRAPHICSLINEHANDLE_H
#define GRAPHICSLINEHANDLE_H

#include "graphicshandle.h"

class GraphicsLineHandle : public GraphicsHandle
{
public:
    explicit GraphicsLineHandle(int handleType, GraphicsSelection *selection, QGraphicsItem *parent = nullptr);

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GRAPHICSLINEHANDLE_H
