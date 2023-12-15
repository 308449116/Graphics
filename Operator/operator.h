#ifndef OPERATOR
#define OPERATOR

#include <QObject>
#include <QPointF>

class ViewGraphics;
class GraphicsItem;
class QGraphicsSceneMouseEvent;

class Operator : public QObject
{
    Q_OBJECT
public:
    enum SelectMode {
        NONE,
        MOVE,
        SIZE,
        ROTATE
    };

    Operator();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, ViewGraphics *view);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, ViewGraphics *view);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, ViewGraphics *view);

    QPointF m_pressedPos;
    QPointF m_lastPos;
    QPointF m_initialPos;
    QPointF m_oppositePos;
    int m_selectMode;
    int m_handleType;
//    QGraphicsPathItem * dashRect;
//    GraphicsItemGroup * selLayer;
};

#endif // OPERATOR

