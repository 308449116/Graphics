#include "itemungroupcmd.h"
#include "viewgraphics.h"

ItemUngroupCmd::ItemUngroupCmd(QList<QSharedPointer<GraphicsAbstractItem>> items,
                               ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view{view}
{
    foreach (auto item, items) {
        if (item->type() == GraphicsItemType::GroupItem) {
            qDebug() << "111 item rotation:" << item->rotation();
            m_groupItemsHash.insert(item, item->getChildItems());
        }
    }
}

void ItemUngroupCmd::undo()
{
    qDebug() << "m_groupItemsHash count:" << m_groupItemsHash.count();
    for (const auto &[item, childItems] : m_groupItemsHash.asKeyValueRange()) {
        qDebug() << "childItems count:" << childItems.count();
        foreach (auto childItem, childItems) {
            qDebug() << "addToGroup";
            item->addToGroup(childItem);
        }
        qDebug() << "item rotation:" << item->rotation();
        m_view->addItem(item);
    }
    this->setText("Undo Ungroup");
}

void ItemUngroupCmd::redo()
{
    m_view->ungroupItems(m_groupItemsHash.keys());
    this->setText("Redo Ungroup");
}
