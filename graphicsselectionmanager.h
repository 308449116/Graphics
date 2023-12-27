#ifndef GRAPHICSSELECTIONMANAGER_H
#define GRAPHICSSELECTIONMANAGER_H

#include <QList>
#include <QPointF>
#include <QHash>
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

    bool isItemSelected(QSharedPointer<GraphicsItem> item) const;

    QList<QSharedPointer<GraphicsItem> > selectedItems() const;

    int collidesWithHandle(QSharedPointer<GraphicsItem> item, const QPointF & point) const;

    QPointF opposite(QSharedPointer<GraphicsItem> item, int handleType) const;

    GraphicsSelection *addItem(ViewGraphics *view, QSharedPointer<GraphicsItem> item);

    void removeItem(QSharedPointer<GraphicsItem> item);

    void updateGeometry(QSharedPointer<GraphicsItem> item);

    void hide(QSharedPointer<GraphicsItem> item);

    void show(QSharedPointer<GraphicsItem> item);

private:
    using SelectionPool = QList<GraphicsSelection *>;
    SelectionPool m_selectionPool;
    QHash<QSharedPointer<GraphicsItem>, GraphicsSelection *> m_usedSelections;
};

#endif // GRAPHICSSELECTIONMANAGER_H
