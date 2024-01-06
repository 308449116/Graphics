#ifndef ITEMRESIZECMD_H
#define ITEMRESIZECMD_H

#include <QPointF>
#include <QUndoCommand>
#include <QSharedPointer>
#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemResizeCmd : public QUndoCommand
{
public:
    explicit ItemResizeCmd(int handleType, QSharedPointer<GraphicsAbstractItem> item, const QPointF &scale,
                           ViewGraphics *view, bool isResized,
                           QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    int m_handleType;
    bool m_isResized;
    const QPointF m_scale;

    ViewGraphics *m_view;
    QSharedPointer<GraphicsAbstractItem> m_item;
};

#endif // ITEMRESIZECMD_H
