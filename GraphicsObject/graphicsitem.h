#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

//enum GraphicsItemType
//{
//    GroupItem = QGraphicsItem::UserType + 1,
//    RectItem,
//    TextItem,
//    BarcodeItem,
//    EllipseItem,
//    ImageItem,
//    TypeCount
//};

class GraphicsItem : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsItem(QObject *parent = nullptr);

    virtual ~GraphicsItem();

    virtual int type() const = 0;

    virtual void updateCoordinate() = 0;

    virtual void stretch(qreal sx, qreal sy, const QPointF &origin) = 0;

    virtual GraphicsItem *duplicate() const = 0;

    virtual QRectF getRect() const;

    void move(const QPointF &point);
    QGraphicsItem *subItem() const;
    QRectF boundingRect() const;

    void setItemName(QString newName);
    QString itemName() const;

    qreal width() const;
    void setWidth(qreal newWidth);

    qreal height() const;
    void setHeight(qreal newHeight);


    QPointF oppositePos() const;
    void setOppositePos(QPointF newOppositePos);

    qreal scaleY() const;
    qreal scaleX() const;
    void setScale(qreal scaleX, qreal scaleY);

//    GraphicsItem *itemParent() const;
//    void setItemParent(GraphicsItem *newItemParent);

    void setRotation(qreal newAngle);
    void setInitAngle(qreal newInitAngle);
    void setGroupAngle(qreal newGroupAngle);
    qreal rotation() const;
    qreal initAngle() const;
    qreal groupAngle() const;

signals:
    void sendUpdateHandle();
    void sendGraphicsItemChange();

private:
    void setChildItemRotation(GraphicsItem *item, qreal angleGroup);

protected:

protected:
    qreal m_initAngle = 0;
    qreal m_groupAngle = 0;
    qreal m_rotationAngle = 0;
    QGraphicsItem *m_subItem = nullptr;
//    GraphicsItem *m_itemParent = nullptr;

    QString m_itemName;
    QRectF m_localRect;
    QRectF m_initialRect;
    QPointF m_oppositePos;
    qreal m_scaleX = 1;
    qreal m_scaleY = 1;
};

#endif // GRAPHICSITEM_H
