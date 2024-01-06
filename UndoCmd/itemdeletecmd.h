#ifndef ITEMDELETECMD_H
#define ITEMDELETECMD_H

#include <QUndoCommand>
#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemDeleteCmd : public QUndoCommand
{
public:
    explicit ItemDeleteCmd(QList<QSharedPointer<GraphicsAbstractItem> > items,
                           ViewGraphics *view, QUndoCommand *parent = nullptr);

    ~ItemDeleteCmd();

    void undo() override;

    void redo() override;

private:
    QList<QSharedPointer<GraphicsAbstractItem> > m_items;
    ViewGraphics *m_view;
};

#endif
