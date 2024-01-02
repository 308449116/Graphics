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
    m_view->moveItems(m_items, QPointF(0, 0), false);
    m_isMoved = false;

    const auto &[initPos, item] = m_items[0];
    setText(QObject::tr("Undo Move %1,%2")
            .arg(initPos.x()).arg(initPos.y()));
}

void ItemMoveCmd::redo()
{
    if (!m_isMoved) {
        m_view->moveItems(m_items, m_offsetPos, false);
    }

    const auto &[initPos, item] = m_items[0];
    QPointF pos = initPos + m_offsetPos;
    setText(QObject::tr("Redo Move %1,%2")
                .arg(pos.x()).arg(pos.y()));
}
