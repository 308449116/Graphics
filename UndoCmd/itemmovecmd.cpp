#include "itemmovecmd.h"
#include "viewgraphics.h"

ItemMoveCmd::ItemMoveCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsItem>>> &items,
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
    for (const auto &[initPos, item] : m_items) {
        item->subItem()->moveBy(-m_offsetPos.x(), -m_offsetPos.y());
        m_view->updateHandle(item);
    }
//    m_view->moveItems(m_items, QPointF(0, 0));
    m_isMoved = false;

    const auto &[initPos, item] = m_items[0];
    setText(QObject::tr("Undo Move %1,%2")
            .arg(initPos.x()).arg(initPos.y()));
}

void ItemMoveCmd::redo()
{
    if (!m_isMoved) {
        for (const auto &[initPos, item] : m_items) {
            item->subItem()->moveBy(m_offsetPos.x(), m_offsetPos.y());
            m_view->updateHandle(item);
        }
    }

    const auto &[initPos, item] = m_items[0];
    QPointF pos = initPos + m_offsetPos;
    setText(QObject::tr("Redo Move %1,%2")
                .arg(pos.x()).arg(pos.y()));
}
