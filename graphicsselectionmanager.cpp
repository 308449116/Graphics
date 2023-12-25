#include "graphicsselectionmanager.h"
#include "graphicsselection.h"
#include "graphicsitem.h"

GraphicsSelectionManager::~GraphicsSelectionManager()
{
    clearSelectionPool();
}

void GraphicsSelectionManager::clear()
{
    if (!m_usedSelections.isEmpty()) {
        for (auto it = m_usedSelections.begin(), mend = m_usedSelections.end(); it != mend; ++it)
            it.value()->setItem(nullptr);
        m_usedSelections.clear();
    }
}

void GraphicsSelectionManager::clearSelectionPool()
{
    clear();
    qDeleteAll(m_selectionPool);
    m_selectionPool.clear();
}

GraphicsSelection *GraphicsSelectionManager::addItem(QGraphicsScene *scene, GraphicsItem *item)
{
    GraphicsSelection *gs = m_usedSelections.value(item);
    if (gs != nullptr) {
        gs->show();
        gs->updateActive();
        return gs;
    }

    // find a free one in the pool
    for (auto *s : std::as_const(m_selectionPool)) {
        if (!s->isUsed()) {
            gs = s;
            break;
        }
    }

    if (gs == nullptr) {
        gs = new GraphicsSelection(scene);
        m_selectionPool.push_back(gs);
    }

    m_usedSelections.insert(item, gs);
    gs->setItem(item);
    qDebug("GraphicsSelection hide item:%p" , gs);
    qDebug("m_selectionPool insert item:%p" , item);
    qDebug() << "m_selectionPool count:" << m_selectionPool.count();
    qDebug() << "m_usedSelections count:" << m_usedSelections.count();
    return gs;
}

GraphicsItem* GraphicsSelectionManager::removeItem(GraphicsItem *item)
{
    GraphicsSelection *s = m_usedSelections.value(item);
    if (!s) {
        return item;
    }


    s->setItem(nullptr);
    m_usedSelections.remove(item);

    if (m_usedSelections.isEmpty()) {
        return nullptr;
    }

    return (*m_usedSelections.begin())->item();
}

bool GraphicsSelectionManager::isItemSelected(GraphicsItem *item) const{
    return  m_usedSelections.contains(item);
}

QList<GraphicsItem *> GraphicsSelectionManager::selectedItems() const
{
    return m_usedSelections.keys();
}

void GraphicsSelectionManager::updateGeometry(GraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->updateGeometry();
    }
}

void GraphicsSelectionManager::hide(GraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->hide();
    }
}

void GraphicsSelectionManager::show(GraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->show();
    }
}

int GraphicsSelectionManager::collidesWithHandle(GraphicsItem *item, const QPointF &point) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->collidesWithHandle(point);
    }

    return 0;
}

QPointF GraphicsSelectionManager::opposite(GraphicsItem *item, int handleType) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->opposite(handleType);
    }

    return QPointF();
}

