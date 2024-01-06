#ifndef ITEMMOVECMD_H
#define ITEMMOVECMD_H

#include <QPointF>
#include <QUndoCommand>
#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemMoveCmd : public QUndoCommand
{
public:
    explicit ItemMoveCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsAbstractItem>>> &items,
                         const QPointF &offsetPos, ViewGraphics *view,
                         bool isMoved, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QList<QPair<QPointF, QSharedPointer<GraphicsAbstractItem>>> m_items;
    QPointF m_offsetPos;
    bool m_isMoved;
};

#endif // ITEMMOVECMD_H
