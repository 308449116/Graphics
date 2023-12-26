#ifndef VIEWGRAPHICS_H
#define VIEWGRAPHICS_H

#include <QGraphicsView>
#include <QSet>
#include "graphicsitemmanager.h"
#include "common.h"

class SceneGraphics;
class GraphicsItem;
class GraphicsSelectionManager;
class GraphicsItemManager;
class QUndoStack;

class ViewGraphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewGraphics(QWidget* parent = nullptr);
    ~ViewGraphics();
    // Create Items
    void createItem(GraphicsItemType type);
    void createItemByCmd(GraphicsItemType type);
    GraphicsItem *createItemByType(GraphicsItemType type);

    void removeItem(GraphicsItem *item);
    void addItem(GraphicsItem *item);

    QString getItemDisplayName(GraphicsItemType type);

    QAction  *createUndoAction();
    QAction  *createRedoAction();

    bool canUndo() const;
    bool canRedo() const;

    bool isUndoCmdEnabled() const;
    void setUndoCmdEnabled(bool newIsUndoCmdEnabled);

protected:
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
//    void selectedStateChange(GraphicsItem *item, bool checked);
//    void updateItemHandle(GraphicsItem *item);
//    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
//    bool trySelectItem(GraphicsItem *item);
    void addItemToSelectionManager(GraphicsItem *item);

private:
    GraphicsSelectionManager *m_selectionManager;
    SceneGraphics *m_scene;
    GraphicsItemManager *m_itemManager;
    QUndoStack *m_undoStack;
    bool m_isUndoCmdEnabled = true;
//    QSet<GraphicsItem *> m_manageItem;
//    bool m_isMousePress = false;
//    GraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
