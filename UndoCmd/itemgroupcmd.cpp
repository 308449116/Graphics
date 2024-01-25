#include "itemgroupcmd.h"
#include "viewgraphics.h"
#include "graphicsitemgroup.h"

ItemGroupCmd::ItemGroupCmd(QList<QSharedPointer<GraphicsItem>> items,
                           ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}, m_childItems(items)
{

}

void ItemGroupCmd::undo()
{
    QList<QSharedPointer<GraphicsItem> > items;
    items.append(m_itemGroup);

    m_view->ungroupItems(items);
    this->setText("Undo Group");
}

void ItemGroupCmd::redo()
{
    if (m_itemGroup.isNull()) {
        m_itemGroup = m_view->groupItems(m_childItems);
    } else {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(m_itemGroup.data());
        foreach (auto item, m_childItems) {
            itemGroup->addToGroup(item);
        }
        m_view->addItem(m_itemGroup);
    }
    this->setText("Redo Group");
}
