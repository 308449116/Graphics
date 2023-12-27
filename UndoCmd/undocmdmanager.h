#ifndef UNDOCMDMANAGER_H
#define UNDOCMDMANAGER_H

#include <QUndoStack>
#include "common.h"

class QUndoView;
class ViewGraphics;
class GraphicsItem;

class UndoCmdManager : public QObject
{
    Q_OBJECT
public:
    enum UndoCmdType
    {
        CreateCmd,
        DeleteCmd,
        DragCmd,
        SizeCmd,
        RoateCmd,
        CountType
    };

    explicit UndoCmdManager(QObject *parent = nullptr);

    // 添加 创建图元命令
    void runCreateCmd(GraphicsItemType type, ViewGraphics *view);

    // 添加 删除图元命令
    void runDeleteCmd(QList<QSharedPointer<GraphicsItem>> items, ViewGraphics *view);

    // 创建Redo Action
    QAction* createRedoAction(void);

    // 创建Undo Action
    QAction* createUndoAction(void);

    // Undo栈相关
    bool isUndoStackEmpty(void) const;
    void cleanUndoStack(void);

    void redo(void);
    void undo(void);

    bool canRedo(void) const;
    bool canUndo(void) const;

    void setUndoLimit(int limit);

private:
    QUndoStack* m_undoStack = nullptr;
};

#endif // UNDOCMDMANAGER_H
