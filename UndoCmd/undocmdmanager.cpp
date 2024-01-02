#include "undocmdmanager.h"
#include "itemcreatecmd.h"
#include "itemdeletecmd.h"
#include "itemmovecmd.h"
#include "viewgraphics.h"
#include <QUndoView>

UndoCmdManager::UndoCmdManager(QObject *parent)
    : QObject{parent}
{
    m_undoStack = new QUndoStack(this);
}

void UndoCmdManager::runCreateCmd(GraphicsItemType type, ViewGraphics *view)
{
    ItemCreateCmd *createCmd = new ItemCreateCmd(type, view);
    m_undoStack->push(createCmd);
}

void UndoCmdManager::runDeleteCmd(QList<QSharedPointer<GraphicsItem>> items, ViewGraphics *view)
{
    ItemDeleteCmd *deleteCmd = new ItemDeleteCmd(items, view);
    m_undoStack->push(deleteCmd);
}

void UndoCmdManager::runMoveCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsItem> > > &items, const QPointF &offsetPos, ViewGraphics *view, bool isMoved)
{
    ItemMoveCmd *moveCmd = new ItemMoveCmd(items, offsetPos, view, isMoved);
    m_undoStack->push(moveCmd);
}

QAction *UndoCmdManager::createRedoAction()
{
    return m_undoStack->createRedoAction(this, tr("Redo"));
}

QAction *UndoCmdManager::createUndoAction()
{
    return m_undoStack->createUndoAction(this, tr("Undo"));
}

bool UndoCmdManager::isUndoStackEmpty() const
{
    return m_undoStack->count() <= 0;
}

void UndoCmdManager::cleanUndoStack()
{
    m_undoStack->clear();
}

void UndoCmdManager::redo()
{
    m_undoStack->redo();
}

void UndoCmdManager::undo()
{
    m_undoStack->undo();
}

bool UndoCmdManager::canRedo() const
{
    return m_undoStack->canRedo();
}

bool UndoCmdManager::canUndo() const
{
    return m_undoStack->canUndo();
}

void UndoCmdManager::setUndoLimit(int limit)
{
    m_undoStack->setUndoLimit(limit);
}

QUndoStack *UndoCmdManager::getUndoStack()
{
    return m_undoStack;
}