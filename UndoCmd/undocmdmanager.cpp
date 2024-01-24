#include "undocmdmanager.h"
#include "itemcreatecmd.h"
#include "itemdeletecmd.h"
#include "itemmovecmd.h"
#include "itemresizecmd.h"
#include "itemrotatecmd.h"
#include "itemcopycmd.h"
#include "itemgroupcmd.h"
#include "itemungroupcmd.h"
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

void UndoCmdManager::runMoveCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsItem> > > &items,
                                const QPointF &offsetPos, ViewGraphics *view, bool isMoved)
{
    ItemMoveCmd *moveCmd = new ItemMoveCmd(items, offsetPos, view, isMoved);
    m_undoStack->push(moveCmd);
}

void UndoCmdManager::runResizeCmd(int handleType, QSharedPointer<GraphicsItem> item, const QPointF &scale,
                                  ViewGraphics *view, bool isResized)
{
    ItemResizeCmd *resizeCmd = new ItemResizeCmd(handleType, item, scale, view, isResized);
    m_undoStack->push(resizeCmd);
}

void UndoCmdManager::runRotateCmd(QSharedPointer<GraphicsItem> item, const qreal angle, ViewGraphics *view)
{
    ItemRotateCmd *rotateCmd = new ItemRotateCmd(item, angle, view);
    m_undoStack->push(rotateCmd);
}

void UndoCmdManager::runCopyCmd(QList<QSharedPointer<GraphicsItem> > items, ViewGraphics *view)
{
    ItemCopyCmd *copyCmd = new ItemCopyCmd(items, view);
    m_undoStack->push(copyCmd);
}

void UndoCmdManager::runGroupCmd(QList<QSharedPointer<GraphicsItem>> items, ViewGraphics *view)
{
    ItemGroupCmd *groupCmd = new ItemGroupCmd(items, view);
    m_undoStack->push(groupCmd);
}

void UndoCmdManager::runUngroupCmd(QList<QSharedPointer<GraphicsItem>> items, ViewGraphics *view)
{
    ItemUngroupCmd *ungroupCmd = new ItemUngroupCmd(items, view);
    m_undoStack->push(ungroupCmd);
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
