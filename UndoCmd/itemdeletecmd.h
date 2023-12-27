#ifndef ITEMDELETECMD_H
#define ITEMDELETECMD_H

#include <QUndoCommand>

class GraphicsItem;
class ViewGraphics;

class ItemDeleteCmd : public QUndoCommand
{
public:
    explicit ItemDeleteCmd(QList<QSharedPointer<GraphicsItem> > items,
                           ViewGraphics *view, QUndoCommand *parent = nullptr);
    ~ItemDeleteCmd();

    void undo(void) override;
    void redo(void) override;

private:
    QList<QSharedPointer<GraphicsItem> > m_items;
    ViewGraphics *m_view;
};

#endif
