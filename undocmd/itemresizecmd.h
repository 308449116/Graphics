#ifndef ITEMRESIZECMD_H
#define ITEMRESIZECMD_H

#include <QPointF>
#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;

class ItemResizeCmd : public QUndoCommand
{
public:
    explicit ItemResizeCmd(int handleType, GraphicsItem *item, const QPointF &scale,
                           ViewGraphics *view, bool isResized,
                           QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    int m_handleType;
    bool m_isResized;
    const QPointF m_scale;

    ViewGraphics *m_view = nullptr;
    GraphicsItem *m_item = nullptr;
};

#endif // ITEMRESIZECMD_H
