#ifndef ITEMUNGROUPCMD_H
#define ITEMUNGROUPCMD_H

#include <QUndoCommand>

class ViewGraphics;

class ItemUngroupCmd : public QUndoCommand
{
public:
    explicit ItemUngroupCmd(ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
};

#endif // ITEMUNGROUPCMD_H
