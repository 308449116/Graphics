#ifndef ITEMUNGROUPCMD_H
#define ITEMUNGROUPCMD_H

#include <QSet>
#include <QUndoCommand>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;

class ItemUngroupCmd : public QUndoCommand
{
public:
    explicit ItemUngroupCmd(QList<QSharedPointer<GraphicsItem>> items,
                            ViewGraphics *view, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    ViewGraphics *m_view;
    QHash<QSharedPointer<GraphicsItem>, QSet<QSharedPointer<GraphicsItem>> > m_groupItemsHash;
//    QHash<QSharedPointer<GraphicsItem>,
//          QSet< std::tuple<QSharedPointer<GraphicsItem> , qreal, qreal> > > m_groupItemsHash;
};

#endif // ITEMUNGROUPCMD_H
