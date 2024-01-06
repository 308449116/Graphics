#ifndef GRAPHICSSELECTIONMANAGER_H
#define GRAPHICSSELECTIONMANAGER_H

#include <QHash>
#include <QList>
#include <QPointF>
#include <QSharedPointer>
#include "graphicsabstracttemplate.h"

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

    bool isItemSelected(QSharedPointer<GraphicsAbstractItem> item) const;

    QList<QSharedPointer<GraphicsAbstractItem> > selectedItems() const;

    int collidesWithHandle(QSharedPointer<GraphicsAbstractItem> item, const QPointF & point) const;

    QPointF opposite(QSharedPointer<GraphicsAbstractItem> item, int handleType) const;

    GraphicsSelection *addItem(ViewGraphics *view, QSharedPointer<GraphicsAbstractItem> item);

    void removeItem(QSharedPointer<GraphicsAbstractItem> item);

    void updateGeometry(QSharedPointer<GraphicsAbstractItem> item);

    void hide(QSharedPointer<GraphicsAbstractItem> item, bool isHideDragHandle);

    void show(QSharedPointer<GraphicsAbstractItem> item);

private:
    using SelectionPool = QList<GraphicsSelection *>;
    SelectionPool m_selectionPool;
    QHash<QSharedPointer<GraphicsAbstractItem>, GraphicsSelection *> m_usedSelections;
};

#endif // GRAPHICSSELECTIONMANAGER_H
