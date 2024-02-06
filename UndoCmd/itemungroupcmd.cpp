#include "itemungroupcmd.h"
#include "viewgraphics.h"
#include "graphicsitemgroup.h"

ItemUngroupCmd::ItemUngroupCmd(QList<GraphicsItem *> items,
                               ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}
{
    foreach (auto item, items) {
        if (item->type() == GraphicsItemType::GroupItem) {
            GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
            m_groupItemsHash.insert(item, itemGroup->getChildItems());
        }
    }
}

ItemUngroupCmd::~ItemUngroupCmd()
{
    if (m_isDeleteItem) {
        foreach (auto itemGroup, m_groupItemsHash.keys()) {
            delete itemGroup;
            itemGroup = nullptr;
        }
    }
}

void ItemUngroupCmd::undo()
{
    m_isDeleteItem = false;
    for (const auto &[groupItem, childItems] : m_groupItemsHash.asKeyValueRange()) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(groupItem);
        foreach (auto childItem, childItems) {
            itemGroup->addToGroup(childItem);
        }
        m_view->addItem(groupItem);

        if (itemGroup->itemGroup()) {
            QGraphicsItemGroup *group =
                qgraphicsitem_cast<QGraphicsItemGroup *>(itemGroup->itemGroup()->subItem());
            if (group) {
                group->addToGroup(itemGroup->subItem());
            }
        }
    }
    this->setText("Undo Ungroup");
}

void ItemUngroupCmd::redo()
{
    m_isDeleteItem = true;
    m_view->ungroupItems(m_groupItemsHash.keys(), false);
    this->setText("Redo Ungroup");
}
