#include "viewgraphics.h"
#include "graphicsselectionmanager.h"
#include "scenegraphics.h"
#include "graphicsitemmanager.h"
#include "itemcreatecmd.h"
#include "itemdeletecmd.h"
#include "graphicsitem.h"

#include <QDebug>
#include <QUndostack>

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
    m_undoStack = new QUndoStack(this);
    m_undoStack->setUndoLimit(5);
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
    connect(m_scene, &SceneGraphics::deleteGraphicsItems, this, &ViewGraphics::removeItems);
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
        createItemByCmd(type);
    } else {
        createItemByType(type);
    }
}

void ViewGraphics::removeItems(QList<GraphicsItem *> items)
{
    if (items.empty()) return;

    if (m_isUndoCmdEnabled) {
        ItemDeleteCmd *deleteCmd = new ItemDeleteCmd(items, this);
        m_undoStack->push(deleteCmd);
    } else {
        foreach (auto item, items) {
            removeItem(item);
        }
    }
}

GraphicsItem * ViewGraphics::createItemByType(GraphicsItemType type)
{
    GraphicsItem *item = m_itemManager->createGraphicsItem(type);
    addItemToSelectionManager(item);
    return item;
}

void ViewGraphics::removeItem(GraphicsItem *item)
{
    if (m_selectionManager->isItemSelected(item)) {
        m_selectionManager->removeItem(item);
    }

    m_itemManager->deleteGraphicsItem(item);
}

void ViewGraphics::createItemByCmd(GraphicsItemType type)
{
    ItemCreateCmd *createCmd = new ItemCreateCmd(type, this);
    m_undoStack->push(createCmd);
}

QString ViewGraphics::getItemDisplayName(GraphicsItemType type)
{
    return m_itemManager->getItemDisplayName(type);
}


void ViewGraphics::addItem(GraphicsItem *item)
{
    m_scene->addItem(item);
    addItemToSelectionManager(item);
}

QAction *ViewGraphics::createUndoAction()
{
    QAction *undoAct = m_undoStack->createUndoAction(this, tr("undo"));
    undoAct->setIcon(QIcon(":/icons/undo.png"));
    return undoAct;
}

QAction *ViewGraphics::createRedoAction()
{
    QAction *redo = m_undoStack->createRedoAction(this, tr("redo"));
    redo->setIcon(QIcon(":/icons/redo.png"));
    return redo;
}

bool ViewGraphics::canUndo() const
{
    return m_undoStack->canUndo();
}

bool ViewGraphics::canRedo() const
{
    return m_undoStack->canRedo();
}

void ViewGraphics::addItemToSelectionManager(GraphicsItem *item)
{
    m_selectionManager->addItem(m_scene, item);
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
