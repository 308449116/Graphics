#ifndef CANVASOPERATORS_H
#define CANVASOPERATORS_H

#include <QPointF>
#include <QGraphicsItem>
class CanvasView;
class QMouseEvent;
class CanvasPathItem;
//class NDAttributeBase;
class CanvasOperBase
{
public:
    CanvasOperBase(CanvasView* view);
    virtual ~CanvasOperBase();

    virtual bool disposePressEvent(QMouseEvent* event);
    virtual bool disposeMoveEvent(QMouseEvent* event);
    virtual bool disposeReleaseEvent(QMouseEvent* event);
    virtual bool disposeKeyPressEvent(QKeyEvent* event);

protected:
    CanvasView* m_pCanvasView = nullptr;
};

// ---------------------------------------------------------------------
// 默认操作器，操作器调度器
class CanvasDefaultOper : public CanvasOperBase
{
public:
    CanvasDefaultOper(CanvasView* view);
    ~CanvasDefaultOper();

    bool disposePressEvent(QMouseEvent* event) override;
    bool disposeMoveEvent(QMouseEvent* event) override;
    bool disposeReleaseEvent(QMouseEvent* event) override;

    bool disposeKeyPressEvent(QKeyEvent* event) override;
};

// ---------------------------------------------------------------------
// 画笔操作器(自由绘制)
class CanvasPenOper : public CanvasOperBase
{
public:
    CanvasPenOper(CanvasView* view);
    ~CanvasPenOper();

    bool disposePressEvent(QMouseEvent* event) override;
    bool disposeMoveEvent(QMouseEvent* event) override;
    bool disposeReleaseEvent(QMouseEvent* event) override;

private:
    CanvasPathItem* m_pPathItem = nullptr;
};

// ---------------------------------------------------------------------
// 矩形选择操作器
class CanvasRectSelectOper : public CanvasOperBase
{
public:
    CanvasRectSelectOper(CanvasView* view);
    ~CanvasRectSelectOper();

    bool disposePressEvent(QMouseEvent* event) override;
    bool disposeMoveEvent(QMouseEvent* event) override;
    bool disposeReleaseEvent(QMouseEvent* event) override;

private:
    QPoint m_pressedViewPos;
    QPointF m_pressedScenePos;
};

// ---------------------------------------------------------------------
// 多选移动操作器
class CanvasMoveSelectedItem : public CanvasOperBase
{
public:
    CanvasMoveSelectedItem(CanvasView* view);
    ~CanvasMoveSelectedItem();

    bool disposePressEvent(QMouseEvent* event) override;
    bool disposeMoveEvent(QMouseEvent* event) override;
    bool disposeReleaseEvent(QMouseEvent* event) override;

private:
    QPointF m_scenePos;
    QList<QGraphicsItem *> m_items;

    QList<NDAttributeBase*> m_xAttributes;
    QList<NDAttributeBase*> m_yAttributes;
    QVector<QVariant> m_xValues;
    QVector<QVariant> m_yValues;

    QVector<QVariant> m_xOldValues;
    QVector<QVariant> m_yOldValues;
};

// ---------------------------------------------------------------------
// 删除操作器
class CanvasDeleteOperator : public CanvasOperBase
{
public:

};

#endif
