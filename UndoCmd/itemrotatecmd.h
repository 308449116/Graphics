#ifndef ITEMROTATECMD_H
#define ITEMROTATECMD_H

#include <QPointF>
#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;

class ItemRotateCmd : public QUndoCommand
{
public:
    explicit ItemRotateCmd(GraphicsItem *item, const qreal initialAngle,
                           ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    qreal m_initialAngle;
    qreal m_rotateAngle;

    ViewGraphics *m_view = nullptr;
    GraphicsItem *m_item = nullptr;
};

#endif // ITEMROTATECMD_H
