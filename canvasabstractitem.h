#ifndef CANVASABSTRACTITEM_H
#define CANVASABSTRACTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

template < typename BaseItem = QGraphicsItem >
class  CanvasAbstractItem : public QObject, public BaseItem
{
    Q_OBJECT

public:
    enum ItemOperator
    {
        t_none,
        t_move,
        t_resize,
        t_rotate
    };

    CanvasAbstractItem(QGraphicsItem* parentItem = nullptr);
    virtual ~CanvasAbstractItem() {}

    // 设置改变大小相关属性
    void setItemResizeable(bool resizeable);
    void setItemResizeRatio(bool resizeRation, qreal rationValue);

    // 设置/获取当前索引
    void setCurrentIndex(int index);
    int getCurrentIndex(void);


protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) final;
    QPainterPath shape() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

//    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    // 自定义元素绘制
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // 处理Item上的类型
    virtual void mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveRotateOperator(const QPointF& scenePos, const QPointF& loacalPos);

    // 处理鼠标释放
    virtual void mouseReleaseMoveOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseReleaseResizeOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseReleaseRotateOperator(const QPointF& scenePos, const QPointF& loacalPos);

    // 获取自定义绘制所需要的矩形
    QRectF getCustomRect(void) const;

    // 属性
//    NDNodeBase* m_pNode = nullptr;

//    void initNodeBase(void);
//    // 通用属性
//    NDRealAttribute* m_pXPostionAttribute = nullptr;
//    NDRealAttribute* m_pYPostionAttribute = nullptr;
//    NDRealAttribute* m_pZPostionAttribute = nullptr;
//    // 宽度和高度属性
//    NDIntAttribute* m_pWidthAttribute = nullptr;
//    NDIntAttribute* m_pHeightAttribute = nullptr;
//    // 旋转属性
//    NDRealAttribute* m_pRotateAttribute = nullptr;

private slots:
//    void onXPostionAttributeValueChanged(const QVariant& value);
//    void onYPostionAttributeValueChanged(const QVariant& value);
//    void onZPostionAttributeValueChanged(const QVariant& value);
//    void onWidthAttributeValueChanged(const QVariant& value);
//    void onHeightAttributeValueChanged(const QVariant& value);
//    void onRotateAttributeValueChanged(const QVariant& value);

protected:
    QSizeF m_size;
    ItemOperator m_itemOper = t_none;

    QPointF m_pos;              // 本地所坐标点击的点
    QPointF m_pressedPos;       // 场景坐标点击的点
    QPointF m_startPos;         // Item再场景坐标的起始坐标
    QTransform m_transform;     // 变换矩阵
    qreal m_startRotate = 0.0;  // 起始旋转角度
    qreal m_rotate = 0.0;       // 当前旋转角度
    QSizeF m_startSize;          // 起始矩形
    QSizeF m_originSize;

    int m_nInterval = 0;
    int m_nEllipseWidth = 12;    // 半径
    qreal m_scaleX = 1;
    qreal m_scaleY = 1;

private:
    // 初始化Icon
    //    void initIcon(void);

    //    static QImage m_closeIcon;
    //    static QImage m_resizeIcon;
    //    static QImage m_rotateIcon;

    QPixmap m_closePixmap = QPixmap(":/icons/close.png");
    QPixmap m_resizePixmap = QPixmap(":/icons/resize.png");
    QPixmap m_rotatePixmap = QPixmap(":/icons/rotate_press.png");

    // 设置是否能够更改尺寸
    bool m_isResizeable = true;
    bool m_isRatioScale = true;
    qreal m_ratioValue = 1.0;

    int m_nIndex = 0;

    // 画笔设置
    QColor m_cPenColor;
    int m_nPenWidth = 1;
    // 画刷设置
    QColor m_cBrushColor;
    QPointF m_centerPos{0, 0};
    QPointF m_originOffset{0, 0};
};
#endif
