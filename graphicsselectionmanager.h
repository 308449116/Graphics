#ifndef GRAPHICSSELECTIONMANAGER_H
#define GRAPHICSSELECTIONMANAGER_H

#include <QList>
#include <QPointF>
#include <QHash>

class GraphicsItem;
class QGraphicsScene;
class GraphicsSelection;

class GraphicsSelectionManager
{
    Q_DISABLE_COPY_MOVE(GraphicsSelectionManager)

public:
    GraphicsSelectionManager() = default;
    ~GraphicsSelectionManager();
    void clear();
    void  clearSelectionPool();
    bool isItemSelected(GraphicsItem *item) const;
    QList<GraphicsItem *> selectedItems() const;
    GraphicsSelection *addItem(QGraphicsScene *scene, GraphicsItem *item);
    GraphicsItem* removeItem(GraphicsItem *item);
    void updateGeometry(GraphicsItem *item);
    void hide(GraphicsItem *item);
    void show(GraphicsItem *item);
    int collidesWithHandle(GraphicsItem *item, const QPointF & point) const;
    QPointF opposite(GraphicsItem *item, int handleType) const;

private:
    using SelectionPool = QList<GraphicsSelection *>;
    SelectionPool m_selectionPool;
    QHash<GraphicsItem *, GraphicsSelection *> m_usedSelections;
};

#endif // GRAPHICSSELECTIONMANAGER_H
