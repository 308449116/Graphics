#include "itemrotatecmd.h"
#include "viewgraphics.h"

ItemRotateCmd::ItemRotateCmd(GraphicsItem *item, const qreal initialAngle,
                             ViewGraphics *view,QUndoCommand *parent)
    : QUndoCommand{parent}, m_initialAngle(initialAngle),
    m_view(view), m_item(item)
{
    m_rotateAngle = item->rotation();
}

void ItemRotateCmd::undo()
{
    m_view->rotateItem(m_item, m_initialAngle);
    setText(QObject::tr("Undo Rotate %1").arg(m_initialAngle));
}

void ItemRotateCmd::redo()
{
    m_view->rotateItem(m_item, m_rotateAngle);
    setText(QObject::tr("Redo Rotate %1").arg(m_rotateAngle));
}
