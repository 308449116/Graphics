#include "itemresizecmd.h"
#include "viewgraphics.h"

ItemResizeCmd::ItemResizeCmd(int handleType, GraphicsItem *item, const QPointF &scale,
                             ViewGraphics *view, bool isResized, QUndoCommand *parent)
    : QUndoCommand{parent}, m_handleType(handleType), m_isResized(isResized),
    m_scale(scale), m_view(view), m_item(item)
{

}

void ItemResizeCmd::undo()
{
    m_isResized = false;
    m_view->resizeItem(m_handleType, m_item, QPointF(1.0/m_scale.x(), 1.0/m_scale.y()));
    setText(QObject::tr("Undo Resize %1,%2 ,name:%3")
                .arg(1.0/m_scale.x(), 8, 'f', 2)
                .arg(1.0/m_scale.y(), 8, 'f', 2)
                .arg(m_item->itemName()));
}

void ItemResizeCmd::redo()
{
    setText(QObject::tr("Redo Resize %1,%2 ,name:%3")
                .arg(m_scale.x(), 8, 'f', 2)
                .arg(m_scale.y(), 8, 'f', 2)
                .arg(m_item->itemName()));

    if (m_isResized) return;

    m_view->resizeItem(m_handleType, m_item, m_scale);
}
