#include "graphicsselectionmanager.h"
#include "graphicsselection.h"
#include "graphicsitem.h"
#include "graphicsitemgroup.h"
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

GraphicsSelection *GraphicsSelectionManager::addItem(ViewGraphics *view, QSharedPointer<GraphicsItem> item)
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

void GraphicsSelectionManager::removeItem(QSharedPointer<GraphicsItem> item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item.data());
        foreach (auto childItem, itemGroup->getChildItems()) {
            deleteItem(childItem);
        }
    }

    deleteItem(item);
}

void GraphicsSelectionManager::deleteItem(QSharedPointer<GraphicsItem> item)
{
    if (m_usedSelections.isEmpty()) {
        return;
    }

    GraphicsSelection *s = m_usedSelections.value(item);
    if (!s) {
        return;
    }

    s->setItem(nullptr);
    m_usedSelections.remove(item);
}

bool GraphicsSelectionManager::isItemSelected(QSharedPointer<GraphicsItem> item) const{
    return  m_usedSelections.contains(item);
}

QList<QSharedPointer<GraphicsItem> > GraphicsSelectionManager::selectedItems() const
{
    return m_usedSelections.keys();
}

void GraphicsSelectionManager::updateHandle(QSharedPointer<GraphicsItem> item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item.data());
        foreach (auto childItem, itemGroup->getChildItems()) {
            this->updateHandle(childItem);
        }
    }

    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->updateHandle();
    }
}

void GraphicsSelectionManager::hide(QSharedPointer<GraphicsItem> item, bool isHideDragHandle)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->hide(isHideDragHandle);
    }
}

void GraphicsSelectionManager::show(QSharedPointer<GraphicsItem> item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->show();
    }
}

void GraphicsSelectionManager::setZValue(QSharedPointer<GraphicsItem> item, qreal z)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->setZValue(z);
    }
}

qreal GraphicsSelectionManager::zValue(QSharedPointer<GraphicsItem> item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->zValue();
    }

    return 0;
}

int GraphicsSelectionManager::collidesWithHandle(QSharedPointer<GraphicsItem> item, const QPointF &point) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->collidesWithHandle(point);
    }

    return 0;
}

QPointF GraphicsSelectionManager::opposite(QSharedPointer<GraphicsItem> item, int handleType) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->opposite(handleType);
    }

    return QPointF();
}

