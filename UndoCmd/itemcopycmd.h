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
    explicit ItemCopyCmd(QList<GraphicsItem *> items, ViewGraphics *view,
                         QUndoCommand *parent = nullptr);

    ~ItemCopyCmd();

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view = nullptr;
    QList<GraphicsItem *> m_items;
    QList<GraphicsItem *> m_itemsCopy;
    QString m_strName;
    bool m_isDeleteItem = false;
};

#endif // ITEMCOPYCMD_H
