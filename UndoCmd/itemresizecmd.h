#ifndef ITEMRESIZECMD_H
#define ITEMRESIZECMD_H

#include <QUndoCommand>

class ItemResizeCmd : public QUndoCommand
{
public:
    explicit ItemResizeCmd(QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
};

#endif // ITEMRESIZECMD_H
