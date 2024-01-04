#ifndef ITEMCOPYCMD_H
#define ITEMCOPYCMD_H

#include <QPointF>
#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;


class ItemCopyCmd : public QUndoCommand
{
public:
    explicit ItemCopyCmd(QList<QSharedPointer<GraphicsItem>> items, ViewGraphics *view,
                         QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QList<QSharedPointer<GraphicsItem>> m_items;
    QList<QSharedPointer<GraphicsItem>> m_itemsCopy;
    QString m_strName;
};

#endif // ITEMCOPYCMD_H
