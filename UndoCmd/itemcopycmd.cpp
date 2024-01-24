#include "itemcopycmd.h"
#include "viewgraphics.h"

ItemCopyCmd::ItemCopyCmd(QList<QSharedPointer<GraphicsItem>> items, ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand{parent}, m_view(view), m_items{items}
{

}

void ItemCopyCmd::undo()
{
    m_view->deleteItems(m_itemsCopy);
    this->setText(QString("Undo Copy [%1]").arg(m_strName));
}

void ItemCopyCmd::redo()
{
    if (m_itemsCopy.isEmpty()) {
        QStringList strs;
        foreach (auto item, m_items) {
            auto itemCopy = item->duplicate();
            m_view->addItem(itemCopy);
            m_itemsCopy.push_back(itemCopy);
            qDebug() << "itemCopy->getItemName():" << itemCopy->itemName();
            strs << itemCopy->itemName();
        }
        m_strName = strs.join(",");
    } else {
        foreach (auto item, m_itemsCopy) {
            m_view->addItem(item);
        }
    }

    this->setText(QString("Redo Copy [%1]").arg(m_strName));
}
