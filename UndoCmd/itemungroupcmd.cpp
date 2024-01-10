#include "itemungroupcmd.h"
#include "viewgraphics.h"

ItemUngroupCmd::ItemUngroupCmd(ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}
{

}

void ItemUngroupCmd::undo()
{
    m_view->groupItems();
    this->setText("Undo Ungroup");
}

void ItemUngroupCmd::redo()
{
    m_view->ungroupItems();
    this->setText("Redo Ungroup");
}
