#ifndef ITEMUNGROUPCMD_H
#define ITEMUNGROUPCMD_H

#include <QSet>
#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;

class ItemUngroupCmd : public QUndoCommand
{
public:
    explicit ItemUngroupCmd(QList<GraphicsItem *> items,
                            ViewGraphics *view, QUndoCommand *parent = nullptr);

    ~ItemUngroupCmd();

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view = nullptr;
    QHash<GraphicsItem *, QSet<GraphicsItem *> > m_groupItemsHash;
    bool m_isDeleteItem = false;
};

#endif // ITEMUNGROUPCMD_H
