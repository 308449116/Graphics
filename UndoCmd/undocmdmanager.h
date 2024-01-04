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

    // 添加 移动图元命令
    void runMoveCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsItem>>> &items,
                    const QPointF &offsetPos, ViewGraphics *view, bool isMoved);

    // 添加 拉伸图元命令
    void runResizeCmd(int handleType, QSharedPointer<GraphicsItem> item, const QPointF &scale,
                      ViewGraphics *view, bool isResized);

    // 添加 旋转图元命令
    void runRotateCmd(QSharedPointer<GraphicsItem> item, const qreal angle, ViewGraphics *view);

    // 添加 拷贝图元命令
    void runCopyCmd(QList<QSharedPointer<GraphicsItem> > items, ViewGraphics *view);

    // 创建Redo Action
    QAction* createRedoAction();

    // 创建Undo Action
    QAction* createUndoAction();

    // Undo栈相关
    bool isUndoStackEmpty() const;

    void cleanUndoStack();

    void redo();

    void undo();

    bool canRedo() const;

    bool canUndo() const;

    void setUndoLimit(int limit);

    QUndoStack* getUndoStack();

private:
    QUndoStack* m_undoStack = nullptr;
};

#endif // UNDOCMDMANAGER_H
