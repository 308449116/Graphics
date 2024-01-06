#ifndef ITEMROTATECMD_H
#define ITEMROTATECMD_H

#include <QPointF>
#include <QUndoCommand>
#include <QSharedPointer>
#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemRotateCmd : public QUndoCommand
{
public:
    explicit ItemRotateCmd(QSharedPointer<GraphicsAbstractItem> item, const qreal initialAngle,
                           ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    qreal m_initialAngle;
    qreal m_rotateAngle;

    ViewGraphics *m_view;
    QSharedPointer<GraphicsAbstractItem> m_item;
};

#endif // ITEMROTATECMD_H
