#include "itemcreatecmd.h"
#include "viewgraphics.h"

ItemCreateCmd::ItemCreateCmd(GraphicsItemType type, ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand(parent), m_type(type), m_view(view), m_item(nullptr)
{
//    QString str("Create %1");
//    this->setText(str.arg(view->getItemDisplayName(type)));
}

ItemCreateCmd::~ItemCreateCmd()
{
    if (m_isDeleteItem && m_item) {
        delete m_item;
        m_item = nullptr;
    }
}

void ItemCreateCmd::undo()
{
    m_isDeleteItem = true;

    if (m_item) {
        m_view->deleteItem(m_item, false);
    }
}

void ItemCreateCmd::redo()
{
    m_isDeleteItem = false;
    if (m_item) {
        m_view->addItem(m_item);
    } else {
        m_item = m_view->createItem(m_type);
        QString str("Create %1");
        this->setText(str.arg(m_item->itemName()));
    }
}
