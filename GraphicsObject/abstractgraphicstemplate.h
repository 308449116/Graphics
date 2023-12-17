#ifndef ABSTRACTGRAPHICSTEMPLATE_H
#define ABSTRACTGRAPHICSTEMPLATE_H

#include <QGraphicsItem>
//#include <QBrush>
//#include <QPen>

template < typename BaseType = QGraphicsItem >
class AbstractGraphicsTemplate : public BaseType
{
public:
    explicit AbstractGraphicsTemplate(QGraphicsItem *parent = nullptr);    virtual ~AbstractGraphicsTemplate(){}
//    virtual QString displayName () const;
//    virtual void control(int dir, const QPointF & delta );
//    virtual bool loadFromXml(QXmlStreamReader * xml ) = 0;
//    virtual bool saveToXml( QXmlStreamWriter * xml ) = 0 ;

    virtual QRectF rect() const;
    virtual int handleCount() const = 0;
    virtual QGraphicsItem *duplicate() const = 0;
    virtual void updateCoordinate() = 0;
    virtual void move(const QPointF &point) = 0;
    virtual void stretch(qreal sx, qreal sy, const QPointF &origin) = 0;

    qreal  width() const;
    void   setWidth(qreal width);

    qreal  height() const;
    void   setHeight (qreal height);

//    QColor brushColor() const;
//    void   setBrushColor(const QColor & color);

//    QBrush brush() const;
//    void   setBrush(const QBrush & brush);

//    QPen   pen() const;
//    void   setPen(const QPen & pen );

//    QColor penColor() const;
protected:
//    virtual void updatehandles(){}
//    void setState(SelectionHandleState st);
//    QBrush m_brush;
//    QPen   m_pen ;
    QRectF m_localRect;
    qreal m_width = 0;
    qreal m_height = 0;
};

#endif // ABSTRACTGRAPHICSTEMPLATE_H
