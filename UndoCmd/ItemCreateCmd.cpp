#include "itemcreatecmd.h"
#include "viewgraphics.h"
#include "graphicsitem.h"

ItemCreateCmd::ItemCreateCmd(GraphicsItemType type, ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand(parent), m_type(type), m_view(view), m_item(nullptr)
{
    QString str("Create %1");
    this->setText(str.arg(view->getItemDisplayName(type)));
}

ItemCreateCmd::~ItemCreateCmd()
{

}

void ItemCreateCmd::undo()
{
    if (m_item) {
        m_view->removeItem(m_item);
    }
}

void ItemCreateCmd::redo()
{
    m_item = m_view->createItemByType(m_type);
}
