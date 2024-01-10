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

    QSharedPointer<GraphicsAbstractItem> createItem(GraphicsItemType type);

    void addItem(QSharedPointer<GraphicsAbstractItem> item);

    // remove Items
    void removeItemsByCmd();

    void removeItem(QSharedPointer<GraphicsAbstractItem> item);

    void removeItems(const QList<QSharedPointer<GraphicsAbstractItem> > &items);

    // move Items
    void moveItemsByCmd(const QList<QPair<QPointF, QSharedPointer<GraphicsAbstractItem>>> &items,
                   const QPointF &pos, bool isMoved = true);

    void moveItems(const QList<QPair<QPointF, QSharedPointer<GraphicsAbstractItem>>> &items,
                   const QPointF &pos);

    // resize Items
    void resizeItemByCmd(int handleType, QSharedPointer<GraphicsAbstractItem> item,
                         const QPointF &scale, bool isResized);

    void resizeItem(int handleType, QSharedPointer<GraphicsAbstractItem> item, const QPointF &scale);

    // rotate Items
    void rotateItemByCmd(QSharedPointer<GraphicsAbstractItem> item, const qreal angle);

    void rotateItem(QSharedPointer<GraphicsAbstractItem> item, const qreal angle);

    // duplicate Items
    void duplicateItemsByCmd();

    // group Items
    void groupItemsByCmd();

    void groupItems();

    // ungroup Items
    void ungroupItemsByCmd();

    void ungroupItems();

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

    QList<QSharedPointer<GraphicsAbstractItem>> selectedItems();

protected:
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
//    void removeItemsByCmd(const QList<QSharedPointer<GraphicsAbstractItem> > &items);
//    void selectedStateChange(GraphicsItem *item, bool checked);
//    void updateItemHandle(GraphicsItem *item);
//    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
    void addGroupItems(QSharedPointer<GraphicsAbstractItem> item);
//    bool trySelectItem(GraphicsItem *item);
    void addItemToSelectionManager(QSharedPointer<GraphicsAbstractItem> item);

private:
    bool m_isUndoCmdEnabled = true;
    SceneGraphics *m_scene;
    GraphicsItemManager *m_itemManager;
    UndoCmdManager *m_undoCmdManager;
    GraphicsSelectionManager *m_selectionManager;
//    QSet<GraphicsItem *> m_manageItem;
//    bool m_isMousePress = false;
    //    GraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
