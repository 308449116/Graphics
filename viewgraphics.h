#ifndef VIEWGRAPHICS_H
#define VIEWGRAPHICS_H

#include <QSet>
#include <QGraphicsView>

#include "common.h"
#include "graphicsitemmanager.h"

class QUndoView;
class QUndoStack;
class SceneGraphics;
class UndoCmdManager;
class GraphicsItemManager;
class GraphicsSelectionManager;

class ViewGraphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewGraphics(QWidget* parent = nullptr);

    ~ViewGraphics();

    // Create Items
    void createItemByCmd(GraphicsItemType type);

    GraphicsItem *createItem(GraphicsItemType type);

    void addItem(GraphicsItem *item);

    // remove Items
    void deleteItemsByCmd();

    void deleteItem(GraphicsItem *item, bool isFreeMemory = true);

    void deleteItems(const QList<GraphicsItem *> &items, bool isFreeMemory = true);

    // move Items
    void moveItemsByCmd(const QList<QPair<QPointF, GraphicsItem *>> &items,
                   const QPointF &pos, bool isMoved = true);

    void moveItems(const QList<QPair<QPointF, GraphicsItem *>> &items,
                   const QPointF &pos);

    // resize Items
    void resizeItemByCmd(int handleType, GraphicsItem *item,
                         const QPointF &scale, bool isResized);

    void resizeItem(int handleType, GraphicsItem *item, const QPointF &scale);

    // rotate Items
    void rotateItemByCmd(GraphicsItem *item, const qreal angle);

    void rotateItem(GraphicsItem *item, const qreal angle);

    // duplicate Items
    void duplicateItemsByCmd();

    // group Items
    void groupItemsByCmd();

    GraphicsItem *groupItems(QList<GraphicsItem *> items);

    // ungroup Items
    void ungroupItemsByCmd();

    void ungroupItems(QList<GraphicsItem *> items, bool isFreeMemory = true);

    // align Items
    void alignItems(AlignType alignType);

    QString getItemDisplayName(GraphicsItemType type);

    QAction *createUndoAction();

    QAction *createRedoAction();

    bool canUndo() const;

    bool canRedo() const;

    bool isUndoCmdEnabled() const;

    void setUndoCmdEnabled(bool newIsUndoCmdEnabled);

    QUndoStack *getUndoStack() const;

    bool isControlModifier() const;

    void setIsControlModifier(bool newIsControlModifier);

    QList<GraphicsItem *> selectedItems();

    QPointF opposite(GraphicsItem *item, int handleType) const;

    void updateHandle(GraphicsItem *item);

    void setZValue(GraphicsItem *item, int increment);

protected:
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
//    void removeItemsByCmd(const QList<GraphicsItem *> &items);
//    void selectedStateChange(GraphicsItem *item, bool checked);
//    void updateItemHandle(GraphicsItem *item);
//    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
    void addGroupItems(GraphicsItem *item);
//    bool trySelectItem(GraphicsItem *item);
    void addItemToSelectionManager(GraphicsItem *item);

private:
    bool m_isUndoCmdEnabled = true;
    SceneGraphics *m_scene = nullptr;
    GraphicsItemManager *m_itemManager = nullptr;
    GraphicsSelectionManager *m_selectionManager = nullptr;
    QUndoStack* m_undoStack = nullptr;

    //    QSet<GraphicsItem *> m_manageItem;
//    bool m_isMousePress = false;
    //    GraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
