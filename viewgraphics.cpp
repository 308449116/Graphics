#include "viewgraphics.h"
#include "graphicsselectionmanager.h"
#include "scenegraphics.h"
#include "graphicsitemmanager.h"
#include "graphicshandle.h"
#include "graphicsitemgroup.h"
#include "undocmdmanager.h"

#include <QAction>
#include <QDebug>
#include <QGraphicsItemGroup>

ViewGraphics::ViewGraphics(QWidget* parent)
    : QGraphicsView{parent}, m_selectionManager(new GraphicsSelectionManager)
{
    int width = 600;
    int height = 400;
//    QRectF rect(-width/2, -height/2, width, height);
    QRectF rect(0, 0, width, height);

    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//    this->setDragMode(QGraphicsView::RubberBandDrag);

    m_scene = new SceneGraphics();
    m_scene->setSceneRect(rect);
    this->setScene(m_scene);

    m_itemManager = new GraphicsItemManager(m_scene);
    m_undoCmdManager = new UndoCmdManager(this);
    m_undoCmdManager->setUndoLimit(5);

//    QGraphicsRectItem *rectItem = new QGraphicsRectItem(rect);

//    QPen pen;
//    pen.setWidth(2);
//    pen.setStyle(Qt::DashLine);
//    QGraphicsLineItem *lineItemX = new QGraphicsLineItem(rect.left(), 0, rect.left() + rect.width(), 0);
//    QGraphicsLineItem *lineItemY = new QGraphicsLineItem(0, rect.top(), 0, rect.top() + rect.height());
//    lineItemX->setPen(pen);
//    lineItemY->setPen(pen);
//    m_scene->addItem(rectItem);
//    m_scene->addItem(lineItemX);
//    m_scene->addItem(lineItemY);
    connect(m_scene, SIGNAL(deleteGraphicsItems(QList<QSharedPointer<GraphicsAbstractItem> >)),
            this, SLOT(removeItems(QList<QSharedPointer<GraphicsAbstractItem> >)));
//    connect(m_scene, &SceneGraphics::handleStateChange, this, &ViewGraphics::handleStateSwitch);
//    connect(m_scene, &SceneGraphics::updateItemHandle, this, &ViewGraphics::updateItemHandle);
}

ViewGraphics::~ViewGraphics()
{
    delete m_selectionManager;
    delete m_itemManager;
    m_scene->deleteLater();
}

void ViewGraphics::createItem(GraphicsItemType type)
{
    if (m_isUndoCmdEnabled) {
        m_undoCmdManager->runCreateCmd(type, this);
    } else {
        createItemByType(type);
    }
}

void ViewGraphics::removeItems(QList<QSharedPointer<GraphicsAbstractItem> > items)
{
    if (items.empty()) return;

    if (m_isUndoCmdEnabled) {
        m_undoCmdManager->runDeleteCmd(items, this);
    } else {
        foreach (auto item, items) {
            removeItem(item);
        }
    }
}

void ViewGraphics::moveItems(const QList<QPair<QPointF, QSharedPointer<GraphicsAbstractItem>>> &items,
                             const QPointF &pos, bool isUndoCmd, bool isMoved)
{
    if (items.empty()) return;

    if (isUndoCmd) {
        if (m_isUndoCmdEnabled) {
            m_undoCmdManager->runMoveCmd(items, pos, this, isMoved);
        }
    } else {
        for (const auto &[initPos, item] : items) {
            moveItem(item, initPos + pos);
        }
    }
}

void ViewGraphics::moveItem(QSharedPointer<GraphicsAbstractItem> item, const QPointF &pos)
{
    item->setPos(pos);
    m_selectionManager->updateGeometry(item);
    //  m_scene->update();
}

void ViewGraphics::resizeItem(int handleType, QSharedPointer<GraphicsAbstractItem> item,
                              const QPointF &scale, bool isUndoCmd)
{
    if (isUndoCmd) {
        if (m_isUndoCmdEnabled ) {
            m_undoCmdManager->runResizeCmd(handleType, item, scale, this, true);
        }
    } else {
        item->stretch(scale.x(), scale.y(), item->mapFromScene(m_selectionManager->opposite(item, handleType)));
        item->updateCoordinate();
        m_selectionManager->updateGeometry(item);
    }
}

void ViewGraphics::rotateItem(QSharedPointer<GraphicsAbstractItem> item, const qreal angle, bool isUndoCmd)
{
    if (isUndoCmd) {
        if (m_isUndoCmdEnabled ) {
            m_undoCmdManager->runRotateCmd(item, angle, this);
        }
    } else {
        item->setRotation(angle);
        m_selectionManager->updateGeometry(item);
    }
}

void ViewGraphics::deleteItems()
{
    QList<QSharedPointer<GraphicsAbstractItem>> items = selectedItems();
    if (items.isEmpty()) return;

    if (m_isUndoCmdEnabled) {
        m_undoCmdManager->runDeleteCmd(items, this);
    } else {
        foreach (auto item, items) {
            removeItem(item);
        }
    }
}

void ViewGraphics::alignItems(AlignType alignType)
{
    QList<QSharedPointer<GraphicsAbstractItem>> items = selectedItems();
    if (items.isEmpty()) return;

    QSharedPointer<GraphicsAbstractItem> refItem = items.first();
    QRectF refRect = refItem->mapRectToScene(refItem->boundingRect());
    QPointF refCenterPos = refRect.center();

    QList<QPair<QPointF, QSharedPointer<GraphicsAbstractItem>>> itemList;
    foreach (auto item, items) {
        itemList.clear();
        QGraphicsItemGroup *g = qgraphicsitem_cast<QGraphicsItemGroup *>(item->parentItem());
        if (g) {
            continue;
        }

        QRectF rect = item->mapRectToScene(item->boundingRect());
        QPointF lastPos = rect.center();
        switch (alignType) {
        case AlignType::TOP_ALIGN:
            lastPos.setY(refCenterPos.y() - (refRect.height() - rect.height()) / 2);
            break;
        case AlignType::BOTTOM_ALIGN:
            lastPos.setY(refCenterPos.y() + (refRect.height() - rect.height()) / 2);
            break;
        case AlignType::LEFT_ALIGN:
            lastPos.setX(refCenterPos.x() - (refRect.width() - rect.width()) / 2);
            break;
        case AlignType::RIGHT_ALIGN:
            lastPos.setX(refCenterPos.x() + (refRect.width() - rect.width()) / 2);
            break;
        case AlignType::HCENTER_ALIGN:
            lastPos.setY(refCenterPos.y());
            break;
        case AlignType::VCENTER_ALIGN:
            lastPos.setX(refCenterPos.x());
            break;
        case AlignType::CENTER_ALIGN:
            lastPos = refCenterPos;
            break;
        default:
            break;
        }

        QPointF initPos = rect.center();
        QPointF movePos = lastPos - initPos;
        if ( !movePos.isNull() ) {
            itemList.push_back(qMakePair(item->pos(), item));
            moveItems(itemList, movePos, true, false);
        }
    }
}

void ViewGraphics::groupItems()
{
    QList<QSharedPointer<GraphicsAbstractItem>> items = selectedItems();
    if (items.isEmpty()) return;

    foreach(auto item, items) {
        m_selectionManager->hide(item, true);
    }

    QSharedPointer<GraphicsAbstractItem> itemGroup = m_itemManager->createGraphicsItemGroup(items);
    m_selectionManager->addItem(this, itemGroup);
}

void ViewGraphics::ungroupItems()
{
    QList<QSharedPointer<GraphicsAbstractItem>> items = selectedItems();
    if (items.isEmpty()) return;

    foreach (auto item, items) {
        m_itemManager->ungroup(item, m_selectionManager);
    }
}

void ViewGraphics::duplicateItems()
{
    QList<QSharedPointer<GraphicsAbstractItem>> items = selectedItems();
    qDebug() << "duplicateItems count:" << items.count();
    if (items.isEmpty()) return;

    if (m_isUndoCmdEnabled) {
        m_undoCmdManager->runCopyCmd(items, this);
    } else {
        foreach (auto item, items) {
            QSharedPointer<GraphicsAbstractItem> itemCopy = item->duplicate();
            addItem(itemCopy);
        }
    }
}

QSharedPointer<GraphicsAbstractItem> ViewGraphics::createItemByType(GraphicsItemType type)
{
    QSharedPointer<GraphicsAbstractItem> item = m_itemManager->createGraphicsItem(type);
    addItemToSelectionManager(item);
    return item;
}

void ViewGraphics::removeItem(QSharedPointer<GraphicsAbstractItem> item)
{
    if (m_selectionManager->isItemSelected(item)) {
        m_selectionManager->removeItem(item);
    }

    m_itemManager->deleteGraphicsItem(item);
}

QString ViewGraphics::getItemDisplayName(GraphicsItemType type)
{
    return m_itemManager->getItemDisplayName(type);
}


void ViewGraphics::addItem(QSharedPointer<GraphicsAbstractItem> item)
{
    addGroupItems(item);
    m_scene->addItem(item.data());
}

void ViewGraphics::addGroupItems(QSharedPointer<GraphicsAbstractItem> item)
{
    //递归添加组的子图元
    if (item->type() == GraphicsItemType::GroupItem) {
        foreach (auto childItem, item->getChildItems()) {
            addGroupItems(childItem);
        }
    }

    addItemToSelectionManager(item);
}

QAction *ViewGraphics::createUndoAction()
{
    QAction *undoAct = m_undoCmdManager->createUndoAction();
    undoAct->setIcon(QIcon(":/icons/undo.png"));
    return undoAct;
}

QAction *ViewGraphics::createRedoAction()
{
    QAction *redo = m_undoCmdManager->createRedoAction();
    redo->setIcon(QIcon(":/icons/redo.png"));
    return redo;
}

bool ViewGraphics::canUndo() const
{
    return m_undoCmdManager->canUndo();
}

bool ViewGraphics::canRedo() const
{
    return m_undoCmdManager->canRedo();
}

void ViewGraphics::addItemToSelectionManager(QSharedPointer<GraphicsAbstractItem> item)
{
    m_selectionManager->addItem(this, item);
//    m_selectionManager->hide(item, false);
    //    connect(item, &GraphicsItem::selectedChange, this, &ViewGraphics::selectedStateChange);
}

bool ViewGraphics::isUndoCmdEnabled() const
{
    return m_isUndoCmdEnabled;
}

void ViewGraphics::setUndoCmdEnabled(bool newIsUndoCmdEnabled)
{
    m_isUndoCmdEnabled = newIsUndoCmdEnabled;
}

QUndoStack *ViewGraphics::getUndoStack() const
{
    return m_undoCmdManager->getUndoStack();
}

bool ViewGraphics::isControlModifier() const
{
    return m_scene->isControlModifier();
}

void ViewGraphics::setIsControlModifier(bool newIsControlModifier)
{
    m_scene->setIsControlModifier(newIsControlModifier);
}


QList<QSharedPointer<GraphicsAbstractItem>> ViewGraphics::selectedItems()
{
    QList<QSharedPointer<GraphicsAbstractItem>> itemList;

    QList<QGraphicsItem *> items = m_scene->selectedItems();
    foreach (auto item, items) {
        GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
        if (handle->handleType() == GraphicsHandle::Drag) {
            itemList << handle->item();
        }
    }

    return itemList;
}

//void ViewGraphics::createTextItem()
//{
//    GraphicsItem *textItem = m_itemManager->createGraphicsItem(GraphicsItemManager::TextItem);
//    addItemToScene(textItem);
//}

//void ViewGraphics::createRectItem()
//{
//    GraphicsItem *rectItem = m_itemManager->createGraphicsItem(GraphicsItemManager::RectItem);
//    addItemToScene(rectItem);
//    /*
//    //    CanvasRectItem* rectItem = new CanvasRectItem();
//    //    rectItem->setSize(100, 100);
//    //    rectItem->setFlag(GraphicsItem::ItemIsSelectable, false);
//    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 100, 100));
//    rectItem->setFlag(GraphicsItem::ItemIsSelectable, true);
//    rectItem->setFlag(GraphicsItem::ItemIsMovable, true);
//    //    CanvasRectItem* rectItem2 = new CanvasRectItem();
//    //    rectItem2->setSize(100, 100);
//    //    rectItem2->setPos(110, 0);
//    //    rectItem2->setFlag(GraphicsItem::ItemIsSelectable, false);
//    //    rectItem2->setSelected(false);

//    //    QGraphicsItemGroup *group = new QGraphicsItemGroup();
//    //    group->setFlags(GraphicsItem::ItemIsMovable |
//    //                    GraphicsItem::ItemIsSelectable);
//    //    group->addToGroup(rectItem);
//    //    group->addToGroup(rectItem2);
//    //    RectGrabber* gabber = new RectGrabber(QSizeF(8, 8));
//    //    DecoratorItemGraphics* item = new DecoratorItemGraphics(rectItem, gabber);
//    m_scene->addItem(rectItem);
//    m_manageItem.insert(rectItem);
//    */
//}

//void ViewGraphics::createBarcoedItem()
//{
////    CanvasBarcodeItem *barcodeitem = new CanvasBarcodeItem();
////    m_scene->addItem(barcodeitem);
//    //    m_manageItem.insert(barcodeitem);
//}

//bool ViewGraphics::isManaged(GraphicsItem *item)
//{
//    return m_manageItem.contains(item);
//}

//void ViewGraphics::manageItem(GraphicsItem *item)
//{
//    m_manageItem.insert(item);
//}

//void ViewGraphics::unmanageItem(GraphicsItem *item)
//{
//    m_manageItem.remove(item);
//}

//int ViewGraphics::collidesWithHandle(GraphicsItem *item, const QPointF &point) const
//{
//    return m_selectionManager->collidesWithHandle(item, point);
//}

//void ViewGraphics::mouseMoveEvent(QMouseEvent *event)
//{
//    //鼠标移动事件
////    QPoint point = event->pos();      //QGraphicsView的坐标
//    QGraphicsView::mouseMoveEvent(event);
//}

//void ViewGraphics::mousePressEvent(QMouseEvent *event)
//{
//    /*
//    //鼠标左键按下事件
//    if ( event->button() != Qt::LeftButton ) return;

//    QPoint point = event->pos();  //QGraphicsView的坐标
//    QPointF pointScene = this->mapToScene(point);         //转换到Scene坐标
//    GraphicsItem *currentItem = m_scene->itemAt(pointScene, this->transform());   //获取光标下的绘图项

//    if (m_currentItem) {

//    } else {
//        if (currentItem != nullptr) {
//            if (trySelectItem(currentItem)) {
//            } else {
//            }
//        } else {
//            m_selectionManager->hide(currentItem);
//        }
//    }
//    QList<GraphicsItem  *> listItem = m_scene->selectedItems();
//    qDebug() << "selectedItems count:" << listItem.count();
//    qDebug() << "items count:" << m_scene->items().count();
//    if (currentItem != nullptr) {
//        if (m_selectionManager->isItemSelected(currentItem)) {
//            m_selectionManager->show(currentItem);
//        } else {
//            m_selectionManager->addItem(m_scene, currentItem);
//        }
//    } else {
//        m_selectionManager->hide(currentItem);
//    }

//    foreach (GraphicsItem  *item, listItem) {
//        qDebug() << "222222222";

////        if (currentItem != nullptr) {
////            qDebug() << "3333333";
////            //                if (!isManaged(currentItem) && !isCentralWidget(currentItem))
////            //                    return ;
////            if (m_selectionManager->isItemSelected(item)) {
////                qDebug() << "44444444444";

////                m_selectionManager->show(item);
////                //                    qDebug() << "item pos:" << QString::asprintf("Item 坐标：%.0f,%.0f", currentItem.x(),currentItem.y());
////                qDebug() << "item pos:" << item->pos();
////                qDebug() << "item scenePos:" << item->scenePos();
////            } else {
////                qDebug() << "555555555";

////                m_selectionManager->addItem(m_scene, item);
////            }
////        } else {
////            qDebug() << "6666666666666";

////            m_selectionManager->hide(item);
////        }
//    }
//    */
//    QGraphicsView::mousePressEvent(event);
//}

//void ViewGraphics::mouseReleaseEvent(QMouseEvent *event)
//{
//    QGraphicsView::mouseReleaseEvent(event);
//}

//bool ViewGraphics::isItemSelected(GraphicsItem *item) const
//{
//    return m_selectionManager->isItemSelected(item);
//}

//QPointF ViewGraphics::opposite(GraphicsItem *item, int handleType) const
//{
//    return m_selectionManager->opposite(item, handleType);
//}

//bool ViewGraphics::trySelectItem(GraphicsItem *item)
//{
//    if (!isManaged(item)) {
//        return false;
//    }

//    if (m_currentItem == item) {
//        return true;
//    }

//    if (item) {
//        if (m_selectionManager->isItemSelected(item)) {
//            m_selectionManager->show(item);
//        } else {
//            m_selectionManager->addItem(m_scene, item);
//        }
//    }

//    m_selectionManager->hide(m_currentItem);
//    m_currentItem = item;
//    return true;
//}

//void ViewGraphics::selectedStateChange(GraphicsItem *item, bool checked)
//{
//    if (item == nullptr) return;

//    if (!m_selectionManager->isItemSelected(item)) {
//        m_selectionManager->addItem(m_scene, item);
//        return;
//    }

//    if (checked) {
//        m_selectionManager->show(item);
//    } else {
//        m_selectionManager->hide(item);
//    }
//}

//void ViewGraphics::updateItemHandle(GraphicsItem *item)
//{
//    m_selectionManager->updateGeometry(item);
//    m_selectionManager->show(item);
//}

//void ViewGraphics::handleStateSwitch(GraphicsItem *item, bool isHide)
//{
//    if (item == nullptr) return;

//    if (isHide) {
//        qDebug() << "handleStateSwitch  isHide:" << isHide;
//        m_selectionManager->hide(item);
//    } else {
//        qDebug() << "handleStateSwitch  isHide:" << isHide;
//        m_selectionManager->show(item);
//    }
//}
