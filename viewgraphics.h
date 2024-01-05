#ifndef VIEWGRAPHICS_H
#define VIEWGRAPHICS_H

#include <QSet>
#include <QGraphicsView>

#include "common.h"
#include "graphicsitemmanager.h"

class QUndoView;
class QUndoStack;
class GraphicsItem;
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
    void createItem(GraphicsItemType type);

    QSharedPointer<GraphicsItem> createItemByType(GraphicsItemType type);

    void addItem(QSharedPointer<GraphicsItem> item);

    // remove Items
    void removeItem(QSharedPointer<GraphicsItem> item);

    // move Items
    void moveItems(const QList<QPair<QPointF, QSharedPointer<GraphicsItem>>> &items,
                   const QPointF &pos, bool isUndoCmd, bool isMoved = true);

    void moveItem(QSharedPointer<GraphicsItem> item, const QPointF &pos);

    // resize Items
    void resizeItem(int handleType, QSharedPointer<GraphicsItem> item, const QPointF &scale, bool isUndoCmd);

    // rotate Items
    void rotateItem(QSharedPointer<GraphicsItem> item, const qreal angle, bool isUndoCmd);

    // duplicate Items
    void duplicateItems();

    // delete Items
    void deleteItems();

    // align Items
    void alignItems(AlignType alignType);

    // group Items
    void groupItems();

    // ungroup Items
    void ungroupItems();

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

protected:
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void removeItems(QList<QSharedPointer<GraphicsItem> > items);
//    void selectedStateChange(GraphicsItem *item, bool checked);
//    void updateItemHandle(GraphicsItem *item);
//    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
//    bool trySelectItem(GraphicsItem *item);
    void addItemToSelectionManager(QSharedPointer<GraphicsItem> item);

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
