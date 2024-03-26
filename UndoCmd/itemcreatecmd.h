#ifndef ITEMCREATECMD_H
#define ITEMCREATECMD_H

#include <QUndoCommand>

#include "viewgraphics.h"

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
    ViewGraphics *m_view = nullptr;
    GraphicsItem *m_item = nullptr;
    bool m_isDeleteItem = false;
};

#endif
