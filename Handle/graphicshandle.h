#ifndef GRAPHICSHANDLE
#define GRAPHICSHANDLE

#include <QGraphicsRectItem>

class QGraphicsRectItem;
class QGraphicsSceneMouseEvent;
class QGraphicsScene;

const static int GRAPHICS_HANDLE_SIZE = 6;

class GraphicsHandle :public QGraphicsRectItem
{
public:
    enum GraphicsHandleState {
        HandleOff,
        HandleActive
    };
    enum HandleType {
        Handle_None = 0 ,
        LeftTop ,
        Top,
        RightTop,
        Right,
        RightBottom,
        Bottom,
        LeftBottom,
        Left,
        Rotate,
        HandleTypeEnd //必须以此类型结尾，增加类型只能从中间插入
    };

    GraphicsHandle(QGraphicsScene* scene , int HandleType , bool control = false );
    int handleType() const  { return m_handleType; }
    void setState(GraphicsHandleState st);
    void move(qreal x, qreal y );
protected:
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *e );
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    const int m_handleType;
    bool   m_controlPoint;
    GraphicsHandleState m_state;
    QColor borderColor;
    QGraphicsScene *m_scene;
};


#endif // GRAPHICSHANDLE

