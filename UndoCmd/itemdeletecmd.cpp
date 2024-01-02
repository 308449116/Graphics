#include "ItemDeleteCmd.h"
#include "graphicsitem.h"
#include "viewgraphics.h"

ItemDeleteCmd::ItemDeleteCmd(QList<QSharedPointer<GraphicsItem> > items, ViewGraphics *view, QUndoCommand *parent)
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

void ItemDeleteCmd::undo(void)
{
    foreach (auto item, m_items) {
        m_view->addItem(item);
    }
}

void ItemDeleteCmd::redo(void)
{
    foreach (auto item, m_items) {
        m_view->removeItem(item);
    }
}