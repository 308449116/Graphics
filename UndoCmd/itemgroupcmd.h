#ifndef ITEMGROUPCMD_H
#define ITEMGROUPCMD_H

#include <QUndoCommand>

class ViewGraphics;

class ItemGroupCmd : public QUndoCommand
{
public:
    explicit ItemGroupCmd(ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
};

#endif // ITEMGROUPCMD_H
