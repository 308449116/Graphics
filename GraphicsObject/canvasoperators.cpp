#include "canvasoperators.h"
//#include "CanvasView.h"
#include "CanvasPathItem.h"
#include "UICanvas/UICanvasItemManager.h"
#include "UICanvasItemBase.h"
#include "NDNodeBase.h"
#include "NDAttributeBase.h"
#include "NDRealAttribute.h"
#include <QMouseEvent>

CanvasOperBase::CanvasOperBase()
    :m_pCanvasView(view)
{

}

CanvasOperBase::~CanvasOperBase()
{

}

bool CanvasOperBase::disposePressEvent(QMouseEvent* event)
{
    return false;
}

bool CanvasOperBase::disposeMoveEvent(QMouseEvent* event)
{
    return false;
}

bool CanvasOperBase::disposeReleaseEvent(QMouseEvent* event)
{
    m_pCanvasView->setCurrentOperator(new CanvasDefaultOper(m_pCanvasView));
    return false;
}

bool CanvasOperBase::disposeKeyPressEvent(QKeyEvent* event)
{
    return false;
}

// ---------------------------------------------------------------------
// 默认操作器，操作器调度器
CanvasDefaultOper::CanvasDefaultOper(CanvasView* view)
    :CanvasOperBase(view)
{

}

CanvasDefaultOper::~CanvasDefaultOper()
{

}

bool CanvasDefaultOper::disposePressEvent(QMouseEvent* event)
{
    auto selectedItems = m_pCanvasView->scene()->selectedItems();
    auto items = m_pCanvasView->items(event->pos());

    CanvasView::CanvasMode mode = m_pCanvasView->getCurrentMode();
    if (mode == CanvasView::t_FreeDrawMode)
    {
        CanvasPenOper* penFreeDrawOper = new CanvasPenOper(m_pCanvasView);
        m_pCanvasView->setCurrentOperator(penFreeDrawOper);
        return penFreeDrawOper->disposePressEvent(event);
    }

    if (selectedItems.size() > 1 && items.size() > 0)
    {
        // 查找选择的列表中，是够包含选中的
        bool hasSelected = false;
        foreach (auto item, items)
        {
            if (item->isSelected())
            {
                hasSelected = true;
                break;
            }
        }
        if (!hasSelected)
            return true;

        // 设置为多选移动操作器(选中的个数>1 且 当前鼠标下有Item时)
        CanvasMoveSelectedItem* moveSelectOper = new CanvasMoveSelectedItem(m_pCanvasView);
        m_pCanvasView->setCurrentOperator(moveSelectOper);
        return moveSelectOper->disposePressEvent(event);
    }
    else if (items.size() <= 0)
    {
        if (mode == CanvasView::t_ArrowMode)
        {
            // 设置为矩形选择操作器（当前点击的为空白）
            CanvasRectSelectOper* rectSelectOper = new CanvasRectSelectOper(m_pCanvasView);
            m_pCanvasView->setCurrentOperator(rectSelectOper);
            return rectSelectOper->disposePressEvent(event);
        }
        else if (mode == CanvasView::t_FreeDrawMode)
        {
            CanvasPenOper* penFreeDrawOper = new CanvasPenOper(m_pCanvasView);
            m_pCanvasView->setCurrentOperator(penFreeDrawOper);
            return penFreeDrawOper->disposePressEvent(event);
        }
    }

    return true;
}

bool CanvasDefaultOper::disposeMoveEvent(QMouseEvent* event)
{
    return false;
}

bool CanvasDefaultOper::disposeReleaseEvent(QMouseEvent* event)
{
    return false;
}

bool CanvasDefaultOper::disposeKeyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QStringList selectedNodeNames;
        // 删除选中的元素
        auto selectedItems = m_pCanvasView->scene()->selectedItems();
        for (auto item : selectedItems)
        {
            UICanvasItemBase* canvasItem = dynamic_cast<UICanvasItemBase*>(item);
            if (canvasItem == nullptr)
                continue;

            selectedNodeNames << canvasItem->getCurrentNode()->getNodeName();
        }

        // 执行删除命令
        if (selectedNodeNames.size() > 0)
            g_currentCanvasManager->deleteCanvasItemByCmd(selectedNodeNames);
    }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
    {
        // 方向键 上和下 微调
        auto selectedItems = m_pCanvasView->scene()->selectedItems();
        QList<NDAttributeBase*> m_attrList;
        QVector<QVariant> m_values;
        for (auto item : selectedItems)
        {
            UICanvasItemBase* canvasItem = dynamic_cast<UICanvasItemBase*>(item);
            if (canvasItem == nullptr)
                continue;

            NDAttributeBase* pAttr = canvasItem->getCurrentNode()->getAttribute("yPt");
            NDRealAttribute* pYPtAttr = qobject_cast<NDRealAttribute*>(pAttr);
            if (pYPtAttr == nullptr)
                continue;

            // 重新设置属性
            qreal yPt = pYPtAttr->getValue().toDouble();
            if (event->key() == Qt::Key_Up)
                yPt -= 2;
            else
                yPt += 2;

            m_attrList << pAttr;
            m_values << yPt;
        }

        g_currentCanvasManager->changedAttributeValues(m_attrList, m_values, true);
    }
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        // 方向键 左和右 微调
        auto selectedItems = m_pCanvasView->scene()->selectedItems();
        QList<NDAttributeBase*> m_attrList;
        QVector<QVariant> m_values;
        for (auto item : selectedItems)
        {
            UICanvasItemBase* canvasItem = dynamic_cast<UICanvasItemBase*>(item);
            if (canvasItem == nullptr)
                continue;

            NDAttributeBase* pAttr = canvasItem->getCurrentNode()->getAttribute("xPt");
            NDRealAttribute* pXPtAttr = qobject_cast<NDRealAttribute*>(pAttr);
            if (pXPtAttr == nullptr)
                continue;

            // 重新设置属性
            qreal xPt = pXPtAttr->getValue().toDouble();
            if (event->key() == Qt::Key_Left)
                xPt -= 2;
            else
                xPt += 2;

            m_attrList << pAttr;
            m_values << xPt;
        }

        g_currentCanvasManager->changedAttributeValues(m_attrList, m_values, true);
    }
    else if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_C)
    {
        // 复制
        g_currentCanvasManager->copySelectNodes();
    }
    else if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_V)
    {
        // 粘贴
        g_currentCanvasManager->pasteCmd();
    }

    return false;
}

// ---------------------------------------------------------------------
// 画笔操作器
CanvasPenOper::CanvasPenOper(CanvasView* view)
    :CanvasOperBase(view)
{
    auto item = g_currentCanvasManager->createCanvasItemByCmd(UICanvasItemManager::t_PathItem);
    m_pPathItem = dynamic_cast<CanvasPathItem*>(item.data());

    m_pPathItem->setPos(0, 0);
    m_pPathItem->setSelected(false);
}

CanvasPenOper::~CanvasPenOper()
{

}

bool CanvasPenOper::disposePressEvent(QMouseEvent* event)
{
    QPointF scenePos = m_pCanvasView->mapToScene(event->pos());
    m_pPathItem->setStartPos(scenePos);

    return CanvasOperBase::disposePressEvent(event);
}

bool CanvasPenOper::disposeMoveEvent(QMouseEvent* event)
{
    QPointF scenePos = m_pCanvasView->mapToScene(event->pos());
    m_pPathItem->addPoint(scenePos);

    return CanvasOperBase::disposeMoveEvent(event);
}

bool CanvasPenOper::disposeReleaseEvent(QMouseEvent* event)
{
    m_pPathItem->endDrawPos();

    m_pCanvasView->cleanAllSelected();
    m_pPathItem->setSelected(true);

    return CanvasOperBase::disposeReleaseEvent(event);
}

// ---------------------------------------------------------------------
// 矩形选择操作器
CanvasRectSelectOper::CanvasRectSelectOper(CanvasView* view)
    :CanvasOperBase(view)
{

}

CanvasRectSelectOper::~CanvasRectSelectOper()
{

}

bool CanvasRectSelectOper::disposePressEvent(QMouseEvent* event)
{
    // 设置为显示选中矩形
    m_pCanvasView->setSelectedRectVisible(true);
    m_pCanvasView->setSelectedRect(QRect());

    // 清除所有选中
    auto items = m_pCanvasView->scene()->selectedItems();
    foreach(auto item, items)
        item->setSelected(false);

    m_pressedViewPos = event->pos();
    m_pressedScenePos = m_pCanvasView->mapToScene(event->pos());

    return CanvasOperBase::disposePressEvent(event);
}

bool CanvasRectSelectOper::disposeMoveEvent(QMouseEvent* event)
{
    QPoint endPos = event->pos();
    m_pCanvasView->setSelectedRect(QRect(m_pressedViewPos, endPos));

    return CanvasOperBase::disposeMoveEvent(event);
}

bool CanvasRectSelectOper::disposeReleaseEvent(QMouseEvent* event)
{
    // 选中被选择的矩形
    QPointF endPos = m_pCanvasView->mapToScene(event->pos());
    qreal xStart = qMin(m_pressedScenePos.x(), endPos.x());
    qreal xEnd = qMax(m_pressedScenePos.x(), endPos.x());
    qreal yStart = qMin(m_pressedScenePos.y(), endPos.y());
    qreal yEnd = qMax(m_pressedScenePos.y(), endPos.y());

    //设置矩形值
    QRectF rect(QPointF(xStart, yStart), QPointF(xEnd, yEnd));
    QList<QGraphicsItem *> items = m_pCanvasView->scene()->items(rect, Qt::IntersectsItemShape);
    foreach(auto item, items)
        item->setSelected(true);

    m_pCanvasView->setSelectedRectVisible(false);

    return CanvasOperBase::disposeReleaseEvent(event);
}

// ---------------------------------------------------------------------
// 多选移动操作器
CanvasMoveSelectedItem::CanvasMoveSelectedItem(CanvasView* view)
    :CanvasOperBase(view)
{

}

CanvasMoveSelectedItem::~CanvasMoveSelectedItem()
{

}

bool CanvasMoveSelectedItem::disposePressEvent(QMouseEvent* event)
{
    m_items = m_pCanvasView->scene()->selectedItems();
    m_scenePos = m_pCanvasView->mapToScene(event->pos());

    foreach (auto item, m_items)
    {
        UICanvasItemBase* pItem = qgraphicsitem_cast<UICanvasItemBase*>(item);
        NDAttributeBase* pXAttr = pItem->getCurrentNode()->getAttribute("xPt");
        NDAttributeBase* pYAttr = pItem->getCurrentNode()->getAttribute("yPt");

        m_xAttributes << pXAttr;
        m_yAttributes << pYAttr;

        m_xValues << pXAttr->getValue();
        m_yValues << pYAttr->getValue();
    }

    m_xOldValues = m_xValues;
    m_yOldValues = m_yValues;
    return CanvasOperBase::disposePressEvent(event);
}

bool CanvasMoveSelectedItem::disposeMoveEvent(QMouseEvent* event)
{
    QPointF pos = m_pCanvasView->mapToScene(event->pos());
    qreal xIntervalue = pos.x() - m_scenePos.x();
    qreal yIntervalue = pos.y() - m_scenePos.y();
    m_scenePos = pos;

    // 重新设置全部选中的坐标
    int count = 0;
    foreach (auto item, m_items)
    {
        QPointF itemPos = item->pos();
        itemPos.setX(itemPos.x() + xIntervalue);
        itemPos.setY(itemPos.y() + yIntervalue);

        item->setPos(itemPos);

        m_xValues[count] = itemPos.x();
        m_yValues[count++] = itemPos.y();
    }

    return CanvasOperBase::disposeMoveEvent(event);
}

bool CanvasMoveSelectedItem::disposeReleaseEvent(QMouseEvent* event)
{
    g_currentCanvasManager->changedAttributeValues(m_xAttributes + m_yAttributes, \
                                                   m_xOldValues + m_yOldValues);
    g_currentCanvasManager->changedAttributeValues(m_xAttributes + m_yAttributes, \
                                                   m_xValues + m_yValues, true);

    return CanvasOperBase::disposeReleaseEvent(event);
}
