#ifndef GRAPHICSSELECTIONMANAGER_H
#define GRAPHICSSELECTIONMANAGER_H

#include <QHash>
#include <QList>
#include <QPointF>
#include <QSharedPointer>

class GraphicsItem;
class ViewGraphics;
class GraphicsSelection;

class GraphicsSelectionManager
{
    Q_DISABLE_COPY_MOVE(GraphicsSelectionManager)

public:
    GraphicsSelectionManager() = default;

    ~GraphicsSelectionManager();

    void clear();

    void clearSelectionPool();

    bool isItemSelected(GraphicsItem *item) const;

    QList<GraphicsItem *> selectedItems() const;

    int collidesWithHandle(GraphicsItem *item, const QPointF & point) const;

    QPointF opposite(GraphicsItem *item, int handleType) const;

    GraphicsSelection *addItem(ViewGraphics *view, GraphicsItem *item);

//    void deleteItem(GraphicsItem *item);

    void updateHandle(GraphicsItem *item);

    void hide(GraphicsItem *item, bool isHideDragHandle);

    void show(GraphicsItem *item);

//    void setZValue(GraphicsItem *item, qreal z);

//    qreal zValue(GraphicsItem *item);

    void removeItem(GraphicsItem *item);

private:
    using SelectionPool = QList<GraphicsSelection *>;
    SelectionPool m_selectionPool;
    QHash<GraphicsItem *, GraphicsSelection *> m_usedSelections;
};

#endif // GRAPHICSSELECTIONMANAGER_H
