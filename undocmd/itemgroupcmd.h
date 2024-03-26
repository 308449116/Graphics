#ifndef ITEMGROUPCMD_H
#define ITEMGROUPCMD_H

#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;

class ItemGroupCmd : public QUndoCommand
{
public:
    explicit ItemGroupCmd(QList<GraphicsItem *> items,
                          ViewGraphics *view, QUndoCommand *parent = nullptr);
    ~ItemGroupCmd();

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view = nullptr;
    GraphicsItem *m_itemGroup = nullptr;
    QList<GraphicsItem *> m_childItems;
    bool m_isDeleteItem = false;
};

#endif // ITEMGROUPCMD_H
