#ifndef ITEMCREATECMD_H
#define ITEMCREATECMD_H

#include <QUndoCommand>
#include "viewgraphics.h"
#include "common.h"

class ItemCreateCmd : public QUndoCommand
{
public:
    explicit ItemCreateCmd(GraphicsItemType type,
                           ViewGraphics *view, QUndoCommand *parent = nullptr);
    ~ItemCreateCmd();

    void undo() override;
    void redo() override;

private:
    GraphicsItemType m_type;
    ViewGraphics *m_view;
    GraphicsItem *m_item;
};

#endif
