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

    QSharedPointer<GraphicsItem> createItem(GraphicsItemType type);

    void addItem(QSharedPointer<GraphicsItem> item);

    // remove Items
    void deleteItemsByCmd();

    void deleteItem(QSharedPointer<GraphicsItem> item);

    void deleteItems(const QList<QSharedPointer<GraphicsItem> > &items);

    // move Items
    void moveItemsByCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsItem>>> &items,
                   const QPointF &pos, bool isMoved = true);

    void moveItems(const QList<QPair<QPointF, QSharedPointer<GraphicsItem>>> &items,
                   const QPointF &pos);

    // resize Items
    void resizeItemByCmd(int handleType, QSharedPointer<GraphicsItem> item,
                         const QPointF &scale, bool isResized);

    void resizeItem(int handleType, QSharedPointer<GraphicsItem> item, const QPointF &scale);

    // rotate Items
    void rotateItemByCmd(QSharedPointer<GraphicsItem> item, const qreal angle);

    void rotateItem(QSharedPointer<GraphicsItem> item, const qreal angle);

    // duplicate Items
    void duplicateItemsByCmd();

    // group Items
    void groupItemsByCmd();

    QSharedPointer<GraphicsItem> groupItems(QList<QSharedPointer<GraphicsItem>> items);

    // ungroup Items
    void ungroupItemsByCmd();

    void ungroupItems(QList<QSharedPointer<GraphicsItem>> items);

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

    QList<QSharedPointer<GraphicsItem>> selectedItems();

    QPointF opposite(QSharedPointer<GraphicsItem> item, int handleType) const;

    void updateHandle(QSharedPointer<GraphicsItem> item);

    void setZValue(QSharedPointer<GraphicsItem> item, int increment);

protected:
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
//    void removeItemsByCmd(const QList<QSharedPointer<GraphicsItem> > &items);
//    void selectedStateChange(GraphicsItem *item, bool checked);
//    void updateItemHandle(GraphicsItem *item);
//    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
    void addGroupItems(QSharedPointer<GraphicsItem> item);
//    bool trySelectItem(GraphicsItem *item);
    void addItemToSelectionManager(QSharedPointer<GraphicsItem> item);

private:
    bool m_isUndoCmdEnabled = true;
    SceneGraphics *m_scene;
    GraphicsItemManager *m_itemManager;
    GraphicsSelectionManager *m_selectionManager;
    QUndoStack* m_undoStack = nullptr;

    //    QSet<GraphicsItem *> m_manageItem;
//    bool m_isMousePress = false;
    //    GraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
