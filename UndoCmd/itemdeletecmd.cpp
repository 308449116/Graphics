#include "ItemDeleteCmd.h"
#include "viewgraphics.h"

ItemDeleteCmd::ItemDeleteCmd(QList<QSharedPointer<GraphicsAbstractItem> > items, ViewGraphics *view, QUndoCommand *parent)
    : QUndoCommand(parent), m_items(items), m_view(view)
{
    // 设置名字
    QString deleteItemString = "Delete [%1]";
    QStringList strs;

    foreach (auto item, items) {
        strs << item->getItemName();
    }
    this->setText(deleteItemString.arg(strs.join(",")));
}

ItemDeleteCmd::~ItemDeleteCmd()
{

}

void ItemDeleteCmd::undo()
{
    foreach (auto item, m_items) {
        m_view->addItem(item);
    }
}

void ItemDeleteCmd::redo()
{
    m_view->deleteItems(m_items);
}
