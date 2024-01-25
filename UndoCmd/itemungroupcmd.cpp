#include "itemungroupcmd.h"
#include "viewgraphics.h"
#include "graphicsitemgroup.h"

ItemUngroupCmd::ItemUngroupCmd(QList<QSharedPointer<GraphicsItem>> items,
                               ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}
{
    foreach (auto item, items) {
        if (item->type() == GraphicsItemType::GroupItem) {
            GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item.data());
            m_groupItemsHash.insert(item, itemGroup->getChildItems());
        }
    }
}

void ItemUngroupCmd::undo()
{
    for (const auto &[groupItem, childItems] : m_groupItemsHash.asKeyValueRange()) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(groupItem.data());
        foreach (auto childItem, childItems) {
            itemGroup->addToGroup(childItem);
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
