#ifndef ITEMGROUPCMD_H
#define ITEMGROUPCMD_H

#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;

class ItemGroupCmd : public QUndoCommand
{
public:
    explicit ItemGroupCmd(QList<QSharedPointer<GraphicsItem>> items,
                          ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QSharedPointer<GraphicsItem> m_itemGroup;
    QList<QSharedPointer<GraphicsItem> > m_childItems;
};

#endif // ITEMGROUPCMD_H
