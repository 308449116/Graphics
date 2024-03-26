#include "itemmovecmd.h"
#include "viewgraphics.h"

ItemMoveCmd::ItemMoveCmd(const QList<GraphicsItem *> &items,
                         const QPointF &offsetPos, ViewGraphics *view,
                         bool isMoved, QUndoCommand *parent)
    : QUndoCommand{parent},
    m_view{view},
    m_items{items},
    m_offsetPos{offsetPos},
    m_isMoved{isMoved}
{

}

void ItemMoveCmd::undo()
{
//    for (const auto &item : m_items) {
//        item->subItem()->moveBy(-m_offsetPos.x(), -m_offsetPos.y());
//        m_view->updateHandle(item);
//    }
    m_view->moveItems(m_items, -m_offsetPos);
    m_isMoved = false;

//    const auto &item = m_items.first();
    setText(QObject::tr("Undo Move %1,%2")
            .arg(-m_offsetPos.x()).arg(-m_offsetPos.y()));
}

void ItemMoveCmd::redo()
{
    if (!m_isMoved) {
//        for (const auto &item : m_items) {
//            item->subItem()->moveBy(m_offsetPos.x(), m_offsetPos.y());
//            m_view->updateHandle(item);
//        }
        m_view->moveItems(m_items, m_offsetPos);
    }

//    const auto &item = m_items.first();
//    QPointF pos = initPos + m_offsetPos;
    setText(QObject::tr("Redo Move %1,%2")
                .arg(m_offsetPos.x()).arg(m_offsetPos.y()));
}
