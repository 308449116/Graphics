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

    virtual QSharedPointer<GraphicsItem> duplicate() const = 0;

    virtual QRectF getRect() const;

    void setRotation(qreal newAngle);
    qreal rotation() const;

    void move(const QPointF &point);
    QGraphicsItem *subItem() const;
    QRectF boundingRect() const;

    void setItemName(QString newName);
    QString itemName() const;

    qreal width() const;
    void setWidth(qreal newWidth);

    qreal height() const;
    void setHeight(qreal newHeight);

    qreal groupAngle() const;
    void setGroupAngle(qreal newGroupAngle);

    QPointF oppositePos() const;
    void setOppositePos(QPointF newOppositePos);

    qreal scaleY() const;
    qreal scaleX() const;
    void setScale(qreal scaleX, qreal scaleY);

    QSharedPointer<GraphicsItem> itemParent() const;
    void setItemParent(QSharedPointer<GraphicsItem> newItemParent);

signals:
    void sendUpdateHandle();
    void sendGraphicsItemChange();

private:
    void setChildItemRotation(QSharedPointer<GraphicsItem> item);

protected:
    qreal m_angle = 0;
    qreal m_groupAngle = 0;
    QGraphicsItem *m_subItem = nullptr;
    QSharedPointer<GraphicsItem> m_itemParent = nullptr;

    QString m_itemName;
    QRectF m_localRect;
    QRectF m_initialRect;
    QPointF m_oppositePos;
    qreal m_scaleX = 1;
    qreal m_scaleY = 1;
};

#endif // GRAPHICSITEM_H
