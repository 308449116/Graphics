#include "graphicsselectionmanager.h"
#include "graphicsselection.h"
#include "common.h"
#include <QDebug>

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

GraphicsSelection *GraphicsSelectionManager::addItem(ViewGraphics *view, QSharedPointer<GraphicsAbstractItem> item)
{
    GraphicsSelection *gs = m_usedSelections.value(item);
    if (gs != nullptr) {
        gs->show();
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
        gs = new GraphicsSelection(view);
        m_selectionPool.push_back(gs);
    }

    m_usedSelections.insert(item, gs);
    gs->setItem(item);
    qDebug("GraphicsSelection hide item:%p" , gs);
    qDebug("m_selectionPool insert item:%p" , item.data());
    qDebug() << "m_selectionPool count:" << m_selectionPool.count();
    qDebug() << "m_usedSelections count:" << m_usedSelections.count();
    return gs;
}

void GraphicsSelectionManager::removeItem(QSharedPointer<GraphicsAbstractItem> item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        foreach (auto childItem, item->getChildItems()) {
            deleteItem(childItem);
        }
    }

    deleteItem(item);
}

void GraphicsSelectionManager::deleteItem(QSharedPointer<GraphicsAbstractItem> item)
{
    GraphicsSelection *s = m_usedSelections.value(item);
    if (!s) {
        return;
    }

    s->setItem(nullptr);
    m_usedSelections.remove(item);

    if (m_usedSelections.isEmpty()) {
        return;
    }
}

bool GraphicsSelectionManager::isItemSelected(QSharedPointer<GraphicsAbstractItem> item) const{
    return  m_usedSelections.contains(item);
}

QList<QSharedPointer<GraphicsAbstractItem> > GraphicsSelectionManager::selectedItems() const
{
    return m_usedSelections.keys();
}

void GraphicsSelectionManager::updateGeometry(QSharedPointer<GraphicsAbstractItem> item, qreal anchorAngle)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->updateGeometry(anchorAngle);
    }
}

void GraphicsSelectionManager::hide(QSharedPointer<GraphicsAbstractItem> item, bool isHideDragHandle)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->hide(isHideDragHandle);
    }
}

void GraphicsSelectionManager::show(QSharedPointer<GraphicsAbstractItem> item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->show();
    }
}

int GraphicsSelectionManager::collidesWithHandle(QSharedPointer<GraphicsAbstractItem> item, const QPointF &point) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->collidesWithHandle(point);
    }

    return 0;
}

QPointF GraphicsSelectionManager::opposite(QSharedPointer<GraphicsAbstractItem> item, int handleType) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->opposite(handleType);
    }

    return QPointF();
}

