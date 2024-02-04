#include "itemcopycmd.h"
#include "viewgraphics.h"

ItemCopyCmd::ItemCopyCmd(QList<GraphicsItem *> items, ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view(view), m_items{items}
{

}

ItemCopyCmd::~ItemCopyCmd()
{
    if (m_isDeleteItem) {
        foreach (auto item, m_itemsCopy) {
            delete item;
            item = nullptr;
        }
    }
}

void ItemCopyCmd::undo()
{
    m_isDeleteItem = true;
    m_view->deleteItems(m_itemsCopy, false);
    this->setText(QString("Undo Copy [%1]").arg(m_strName));
}

void ItemCopyCmd::redo()
{
    m_isDeleteItem = false;
    if (m_itemsCopy.isEmpty()) {
        m_itemsCopy = m_view->duplicateItems(m_items);
        QStringList strs;
        foreach (auto item, m_itemsCopy) {
//            auto itemCopy = item->duplicate();
//            m_view->addItem(itemCopy);
//            m_itemsCopy.push_back(itemCopy);
            qDebug() << "itemCopy->getItemName():" << item->itemName();
            strs << item->itemName();
        }
        m_strName = strs.join(",");
    } else {
        foreach (auto item, m_itemsCopy) {
            m_view->addItem(item);
        }
    }

    this->setText(QString("Redo Copy [%1]").arg(m_strName));
}
