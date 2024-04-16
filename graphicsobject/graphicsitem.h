#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

const static int GRID_SIZE = 10;

enum GraphicsItemType
{
    GroupItem = QGraphicsItem::UserType + 1,
    RectItem,
    TextItem,
    BarcodeItem,
    EllipseItem,
    ImageItem,
    TypeCount
};

class NodeBase;
class GraphicsItemGroup;
class QXmlStreamReader;
class QXmlStreamWriter;

class GraphicsItem : public QObject
{
    Q_OBJECT

public:
    explicit GraphicsItem(QObject *parent = nullptr);

    virtual ~GraphicsItem();

    virtual int type() const = 0;

    virtual void init() = 0;

    virtual void updateCoordinate() = 0;

    virtual bool loadFromXml(QXmlStreamReader *xml) = 0;

    virtual bool saveToXml( QXmlStreamWriter *xml) = 0 ;

    virtual void stretch(qreal sx, qreal sy, const QPointF &origin) = 0;

    virtual GraphicsItem *duplicate() const = 0;

    virtual QRectF getRect() const;

    QString uid() const { return m_uid; }
    void setUid(const QString &uid);

    void setPos(const QPointF &pos);
    void setPos(qreal x, qreal y);
    QPointF pos() const;

    void moveBy(const QPointF &point);
    void moveBy(qreal x, qreal y);
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

    void setRotation(qreal newAngle, bool isSendChanged = true);
    void setInitAngle(qreal newInitAngle);
    void setGroupAngle(qreal newGroupAngle);
    qreal rotation() const;
    qreal initAngle() const;
    qreal groupAngle() const;

    GraphicsItemGroup *itemGroup() const;
    void setItemGroup(GraphicsItemGroup *newItemGroup);

//    QGraphicsItemGroup *itemAncestor() const;
//    void setItemAncestor(QGraphicsItemGroup *newItemAncestor);

    qreal zValue() const;
    void setZValue(qreal newZValue);

    NodeBase *getCurrentNode() const;

    void updateBaseAttribute();
    void updateXYAttribute();

signals:
    void sendUpdateHandle();
    void sendGraphicsItemChanged();
    void sendZValueChanged();
    void sendItemNameChanged(const QString &newName, const QString &oldName);

public slots:
    void onXPositionAttributeValueChanged(const QVariant& value);
    void onYPositionAttributeValueChanged(const QVariant& value);
//    void onZPositionAttributeValueChanged(const QVariant& value);
    void onWidthAttributeValueChanged(const QVariant& value);
    void onHeightAttributeValueChanged(const QVariant& value);
    void onRotateAttributeValueChanged(const QVariant& value);
    void onNameAttributeValueChanged(const QVariant &value);
    void onIDAttributeValueChanged(const QVariant &value);

protected:
    void setChildItemRotation(GraphicsItem *item, qreal angleGroup);
    void writeBaseAttributes(QXmlStreamWriter *xml);
    void readBaseAttributes(QXmlStreamReader *xml);

protected:
    qreal m_initAngle = 0;
    qreal m_groupAngle = 0;
    qreal m_rotationAngle = 0;
    qreal m_zValue = 0;
    QGraphicsItem *m_subItem = nullptr;
//    QGraphicsItemGroup *m_itemAncestor = nullptr;
    GraphicsItemGroup *m_itemGroup = nullptr;
    // 属性
    NodeBase *m_AtrributeNode = nullptr;

    QString m_uid;
    QString m_itemName;
    QRectF m_localRect;
    QRectF m_initialRect;
    QPointF m_oppositePos;
    qreal m_scaleX = 1;
    qreal m_scaleY = 1;
};

#endif // GRAPHICSITEM_H
