#ifndef DRAWTOOL
#define DRAWTOOL


#include "drawobj.h"
#include "drawscene.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QAbstractGraphicsShapeItem;
QT_END_NAMESPACE

class ViewGraphics;
class GraphicsItem;
class GraphicsPolygonItem;
enum DrawShape
{
    selection ,
    rotation  ,
    line ,
    rectangle ,
    roundrect ,
    ellipse ,
    bezier,
    polygon,
    polyline,
};

class Operator
{
public:
    Operator( DrawShape shape );
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event ,ViewGraphics *scene );
    DrawShape m_drawShape;
    bool m_hoverSizer;

    static Operator * findTool( DrawShape drawShape );
    static QList<Operator*> c_tools;
    static QPointF c_down;
    static quint32 c_nDownFlags;
    static QPointF c_last;
    static DrawShape c_drawShape;
};

class Operator : public Operator
{
public:
    Operator();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene );
    QPointF initialPositions;
    QPointF opposite_;
    QGraphicsPathItem * dashRect;
    GraphicsItemGroup * selLayer;
};

class  RotationTool : public Operator
{
public:
    RotationTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene );
    qreal lastAngle;
    QGraphicsPathItem * dashRect;
};

class RectTool : public Operator
{
public:
    RectTool(DrawShape drawShape);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene );
    GraphicsItem * item;
};

class PolygonTool : public Operator
{
public:
    PolygonTool(DrawShape shape );
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , ViewGraphics * scene );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event ,ViewGraphics *scene );
    GraphicsPolygonItem * item;
    int m_nPoints;
    QPointF initialPositions;

};

#endif // DRAWTOOL

