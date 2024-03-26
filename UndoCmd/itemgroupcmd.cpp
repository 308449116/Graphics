#include "itemgroupcmd.h"
#include "viewgraphics.h"
#include "graphicsobject/graphicsitemgroup.h"

ItemGroupCmd::ItemGroupCmd(QList<GraphicsItem *> items,
                           ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}, m_childItems(items)
{

}

ItemGroupCmd::~ItemGroupCmd()
{
    if (m_isDeleteItem && m_itemGroup) {
        delete m_itemGroup;
        m_itemGroup = nullptr;
    }
}

void ItemGroupCmd::undo()
{
    QList<GraphicsItem *> items;
    items.append(m_itemGroup);

    m_isDeleteItem = true;
    m_view->ungroupItems(items, false);
    this->setText("Undo Group");
}

void ItemGroupCmd::redo()
{
    m_isDeleteItem = false;
    if (m_itemGroup == nullptr) {
        m_itemGroup = m_view->groupItems(m_childItems);
    } else {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(m_itemGroup);
        for (auto item : m_childItems) {
            itemGroup->addToGroup(item);
        }
        m_view->addItem(m_itemGroup);
    }
    this->setText("Redo Group");
}
