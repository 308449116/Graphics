#ifndef ITEMUNGROUPCMD_H
#define ITEMUNGROUPCMD_H

#include <QUndoCommand>

#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemUngroupCmd : public QUndoCommand
{
public:
    explicit ItemUngroupCmd(QList<QSharedPointer<GraphicsAbstractItem>> items,
                            ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QHash<QSharedPointer<GraphicsAbstractItem>, QSet<QSharedPointer<GraphicsAbstractItem>> > m_groupItemsHash;
};

#endif // ITEMUNGROUPCMD_H
