#ifndef ITEMMOVECMD_H
#define ITEMMOVECMD_H

#include <QUndoCommand>

class ItemMoveCmd : public QUndoCommand
{
public:
    explicit ItemMoveCmd(QUndoCommand *parent = nullptr);

//    void undo(void) override;
//    void redo(void) override;

private:
//    QList<QSharedPointer<GraphicsItem> > m_items;
//    ViewGraphics *m_view;

};

#endif // ITEMMOVECMD_H
