#ifndef ITEMMOVECMD_H
#define ITEMMOVECMD_H

#include <QPointF>
#include <QUndoCommand>

class GraphicsItem;
class ViewGraphics;

class ItemMoveCmd : public QUndoCommand
{
public:
    explicit ItemMoveCmd(const QList<GraphicsItem *> &items,
                         const QPointF &offsetPos, ViewGraphics *view,
                         bool isMoved, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view = nullptr;
    QList<GraphicsItem *> m_items;
    QPointF m_offsetPos;
    bool m_isMoved;
};

#endif // ITEMMOVECMD_H
