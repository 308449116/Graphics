#ifndef GRAPHICSABSTRACTTEMPLATE_H
#define GRAPHICSABSTRACTTEMPLATE_H

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include <QSharedPointer>

template < typename BaseType = QGraphicsItem >
class GraphicsAbstractTemplate : public BaseType
{
public:
    explicit GraphicsAbstractTemplate(QGraphicsItem *parent = nullptr);
    virtual ~GraphicsAbstractTemplate(){}
//    virtual QString displayName () const;
//    virtual void control(int dir, const QPointF & delta );
//    virtual bool loadFromXml(QXmlStreamReader * xml ) = 0;
//    virtual bool saveToXml( QXmlStreamWriter * xml ) = 0 ;
//    virtual QSharedPointer<QGraphicsItem> duplicate() const;

    virtual QRectF getRect() const;

    virtual qreal getRatio() const;

    virtual void updateCoordinate();

    virtual void move(const QPointF &point);

    virtual void stretch(qreal sx, qreal sy, const QPointF &origin);

    virtual void rotate(QPointF rotatePos, QPointF lastPos);

    qreal  width() const;

    void   setWidth(qreal width);

    qreal  height() const;

    void   setHeight (qreal height);

    QColor brushColor() const;

    void   setBrushColor(const QColor &color);

    QBrush brush() const;

    void   setBrush(const QBrush &brush);

    QPen   pen() const;

    void   setPen(const QPen &pen);

    QColor penColor() const;

protected:
    void qt_graphicsItem_highlightSelected(QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option);
//    virtual void updatehandles(){}
//    void setState(SelectionHandleState st);
    qreal m_width = 0;
    qreal m_height = 0;
    qreal m_ratio = 1;
    QBrush m_brush;
    QPen   m_pen ;
    QRectF m_localRect;
    QRectF m_initialRect;
};

using GraphicsAbstractItem = GraphicsAbstractTemplate<QGraphicsItem>;

#endif // GRAPHICSABSTRACTTEMPLATE_H
