#ifndef ITEMCOPYCMD_H
#define ITEMCOPYCMD_H

#include <QPointF>
#include <QUndoCommand>
#include <QSharedPointer>
#include "graphicsabstracttemplate.h"

class ViewGraphics;

class ItemCopyCmd : public QUndoCommand
{
public:
    explicit ItemCopyCmd(QList<QSharedPointer<GraphicsAbstractItem>> items, ViewGraphics *view,
                         QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QList<QSharedPointer<GraphicsAbstractItem>> m_items;
    QList<QSharedPointer<GraphicsAbstractItem>> m_itemsCopy;
    QString m_strName;
};

#endif // ITEMCOPYCMD_H
