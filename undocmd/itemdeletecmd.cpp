#include "ItemDeleteCmd.h"
#include "viewgraphics.h"

ItemDeleteCmd::ItemDeleteCmd(QList<GraphicsItem *> items, ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand(parent), m_items(items), m_view(view)
{
    // 设置名字
    QString deleteItemString = "Delete [%1]";
    QStringList strs;

    for (auto item : items) {
        strs << item->itemName();
    }
    this->setText(deleteItemString.arg(strs.join(",")));
}

ItemDeleteCmd::~ItemDeleteCmd()
{
    if (m_isDeleteItem) {
        for (auto item : m_items) {
            delete item;
            item = nullptr;
        }
    }
}

void ItemDeleteCmd::undo()
{
    for (auto item : m_items) {
        m_view->addItem(item);
    }
    m_isDeleteItem = false;
}

void ItemDeleteCmd::redo()
{
    m_isDeleteItem = true;
//    foreach (auto item, m_items) {
//        item->setItemAncestor(item->subItem()->group());
//    }
    m_view->deleteItems(m_items, false);
}
