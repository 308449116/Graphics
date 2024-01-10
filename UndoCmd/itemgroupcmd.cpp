#include "itemgroupcmd.h"
#include "viewgraphics.h"

ItemGroupCmd::ItemGroupCmd(ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}
{

}

void ItemGroupCmd::undo()
{
    m_view->ungroupItems();
    this->setText("Undo Group");
}

void ItemGroupCmd::redo()
{
    m_view->groupItems();
    this->setText("Redo Group");
}
