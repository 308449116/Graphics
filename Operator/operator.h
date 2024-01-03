#ifndef OPERATOR
#define OPERATOR

#include <QObject>
#include <QPointF>
#include <QTransform>

class QGraphicsScene;
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
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsScene *scene);

private:
    qreal CalculatingAngle(GraphicsItem *item, const QPointF &point);
    qreal m_lastAngle;
    qreal m_currentAngle;
    QPointF m_pressedScenePos;
    QPointF m_pressedPos;
    QPointF m_lastScenePos;
    QPointF m_initialPos;
    QPointF m_oppositePos;
    int m_selectMode;
    int m_handleType;
    bool m_hideHandleSended;
//    QGraphicsPathItem * dashRect;
//    GraphicsItemGroup * selLayer;
};

#endif // OPERATOR

