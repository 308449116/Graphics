#include "itemungroupcmd.h"
#include "viewgraphics.h"

ItemUngroupCmd::ItemUngroupCmd(QList<QSharedPointer<GraphicsItem>> items,
                               ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}
{
    foreach (auto item, items) {
        if (item->type() == GraphicsItemType::GroupItem) {
            m_groupItemsHash.insert(item, item->getChildItems());
        }
    }
}

void ItemUngroupCmd::undo()
{
    for (const auto &[groupItem, childItems] : m_groupItemsHash.asKeyValueRange()) {
        foreach (auto childItem, childItems) {
            groupItem->addToGroup(childItem);
        }
        m_view->addItem(groupItem);
    }
    this->setText("Undo Ungroup");
}

void ItemUngroupCmd::redo()
{
    m_view->ungroupItems(m_groupItemsHash.keys());
    this->setText("Redo Ungroup");
}
