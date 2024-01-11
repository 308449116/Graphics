#ifndef ITEMGROUPCMD_H
#define ITEMGROUPCMD_H

#include <QUndoCommand>

#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemGroupCmd : public QUndoCommand
{
public:
    explicit ItemGroupCmd(QList<QSharedPointer<GraphicsAbstractItem>> items,
                          ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QSharedPointer<GraphicsAbstractItem> m_itemGroup;
    QList<QSharedPointer<GraphicsAbstractItem> > m_childItems;
};

#endif // ITEMGROUPCMD_H
