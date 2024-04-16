#include "viewgraphics.h"
#include "scenegraphics.h"

#include "handle/graphicshandle.h"
#include "handle/graphicsselectionmanager.h"
#include "graphicsobject/graphicsitemgroup.h"
#include "graphicsobject/graphicsitemmanager.h"
#include "attributemodel/nodebase.h"
#include "attributemodel/nodemanager.h"
#include "utils/attribute_constants.h"

#include "undocmd/itemcreatecmd.h"
#include "undocmd/itemdeletecmd.h"
#include "undocmd/itemmovecmd.h"
#include "undocmd/itemresizecmd.h"
#include "undocmd/itemrotatecmd.h"
#include "undocmd/itemcopycmd.h"
#include "undocmd/itemgroupcmd.h"
#include "undocmd/itemungroupcmd.h"
#include "undocmd/itemattributechangedcmd.h"

#include <QUndoView>
#include <QAction>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QFile>
#include <QWheelEvent>

using namespace Utils::Constants;

ViewGraphics::ViewGraphics(QWidget* parent)
    : QGraphicsView{parent}, m_selectionManager(new GraphicsSelectionManager)
{
    int width = 600;
    int height = 400;
//    QRectF rect(-width/2, -height/2, width, height);
    QRectF rect(0, 0, width, height);

    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setDragMode(QGraphicsView::RubberBandDrag);

    m_scene = new SceneGraphics();
    m_scene->setSceneRect(rect);
    this->setScene(m_scene);

    GraphicsItemManager::getInstance()->setCurrentGraphicsView(this);
//    m_itemManager = new GraphicsItemManager(m_scene);
    m_undoStack = new QUndoStack(this);

    connect(m_scene, &SceneGraphics::deleteGraphicsItems, this, &ViewGraphics::deleteItemsByCmd);
    connect(m_scene, &SceneGraphics::selectionChanged, this, &ViewGraphics::itemSelectedChanged);
    connect(m_scene, &SceneGraphics::sceneRectChanged, this, [this] () {
        m_modified = true;
        emit changed();
    });

    connect(g_nodeManager, &NodeManager::signalAttrValueChanged, \
            this, &ViewGraphics::onAttributeValueChanged);

//    connect(m_undoStack, &QUndoStack::canRedoChanged, this, [this](){
//        qDebug() << "canRedoChanged count:" << m_undoStack->count();
//    });
//    connect(m_undoStack, &QUndoStack::canUndoChanged, this, [this](){
//        qDebug() << "canUndoChanged count:" << m_undoStack->count();
//    });
//    m_undoStack->setUndoLimit(5);

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
//    connect(m_scene, SIGNAL(deleteGraphicsItems(QList<GraphicsItem *>)),
//            this, SLOT(removeItemsByCmd(QList<GraphicsItem *>)));
//    connect(m_scene, &SceneGraphics::handleStateChange, this, &ViewGraphics::handleStateSwitch);
//    connect(m_scene, &SceneGraphics::updateItemHandle, this, &ViewGraphics::updateItemHandle);
}

ViewGraphics::~ViewGraphics()
{
    delete m_selectionManager;
//    delete m_itemManager;
    m_scene->deleteLater();
}

void ViewGraphics::createItemByCmd(GraphicsItemType type)
{
    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemCreateCmd *createCmd = new ItemCreateCmd(type, this);
        m_undoStack->push(createCmd);
    } else {
        createItem(type);
    }
}

GraphicsItem *ViewGraphics::createItem(GraphicsItemType type)
{
    m_modified = true;
    GraphicsItem *item = GraphicsItemManager::getInstance()->createGraphicsItem(type);
    addItem(item);
    return item;
}

void ViewGraphics::deleteItemsByCmd()
{
//    QList<GraphicsItem *> items = selectedItems();
    QList<GraphicsItem *> itemList;
    QList<GraphicsItem *> itemTempList = selectedItems();
    for (auto item : itemTempList) {
        if (item->subItem()->group()) {
            continue;
        }
        itemList << item;
    }

    if (itemList.isEmpty()) return;

    m_modified = true;
    emit changed();
    if (m_isUndoCmdEnabled) {
        ItemDeleteCmd *deleteCmd = new ItemDeleteCmd(itemList, this);
        m_undoStack->push(deleteCmd);
    } else {
        deleteItems(itemList);
    }

//    qDebug() << "========== items.count:" << items().count();
}

void ViewGraphics::deleteItems(const QList<GraphicsItem *> &items, bool isFreeMemory)
{
    for (auto item : items) {
        deleteItem(item, isFreeMemory);
    }
}

void ViewGraphics::deleteItem(GraphicsItem *item, bool isFreeMemory)
{
    removeItem(item);
    m_scene->removeItem(item);
    m_scene->update();
    this->update();
    if (isFreeMemory) {
        delete item;
        item = nullptr;
    }
}

void ViewGraphics::moveItemsByCmd(const QList<GraphicsItem *> &items,
                             const QPointF &pos, bool isMoved)
{
    if (items.empty()) return;

    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemMoveCmd *moveCmd = new ItemMoveCmd(items, pos, this, isMoved);
        m_undoStack->push(moveCmd);
    } else {
        moveItems(items, pos);
    }
}

void ViewGraphics::moveItems(const QList<GraphicsItem *> &items,
                             const QPointF &pos)
{
    for (const auto &item : items) {
        item->moveBy(pos);
        m_selectionManager->updateHandle(item);
    }
}

void ViewGraphics::resizeItemByCmd(int handleType, GraphicsItem *item,
                                   const QPointF &scale, bool isResized)
{
    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemResizeCmd *resizeCmd = new ItemResizeCmd(handleType, item, scale, this, isResized);
        m_undoStack->push(resizeCmd);
    } else {
        resizeItem(handleType, item, scale);
    }
}

void ViewGraphics::resizeItem(int handleType, GraphicsItem *item,
                              const QPointF &scale)
{
    const QPointF &oppositePos = item->subItem()->mapFromScene(m_selectionManager->opposite(item, handleType));
//    item->setOppositePos(oppositePos);
    item->stretch(scale.x(), scale.y(), oppositePos);
    item->updateCoordinate();
    m_selectionManager->updateHandle(item);

    if (item->subItem()->parentItem()) {
        emit item->sendGraphicsItemChanged();
    }
}

void ViewGraphics::rotateItemByCmd(GraphicsItem *item, const qreal angle)
{
    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemRotateCmd *rotateCmd = new ItemRotateCmd(item, angle, this);
        m_undoStack->push(rotateCmd);
    } else {
        rotateItem(item, angle);
    }
}

void ViewGraphics::rotateItem(GraphicsItem *item, const qreal angle)
{
    item->setRotation(angle);
    m_selectionManager->updateHandle(item);
}

void ViewGraphics::alignItems(AlignType alignType)
{
    QList<GraphicsItem *> items = selectedItems();
    if (items.isEmpty()) return;

    GraphicsItem *refItem = items.first();
    QRectF refRect = refItem->subItem()->mapRectToScene(refItem->boundingRect());
    QPointF refCenterPos = refRect.center();

    QList<GraphicsItem *> itemList;
    for (auto item : items) {
        itemList.clear();
        QGraphicsItemGroup *group = qgraphicsitem_cast<QGraphicsItemGroup *>(item->subItem()->parentItem());
        if (group) {
            continue;
        }

        QRectF rect = item->subItem()->mapRectToScene(item->boundingRect());
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
            m_modified = true;
            emit changed();

            itemList.push_back(item);
            moveItemsByCmd(itemList, movePos, false);
        }
    }
}

void ViewGraphics::groupItemsByCmd()
{
    QList<GraphicsItem *> items = selectedItems();
    if (items.count() <= 1) {
        return;
    }

    for (auto item : items) {
        if (item->subItem()->group()) {
            //不允许和组中元素组合成新的组
            return;
        }
    }

    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemGroupCmd *groupCmd = new ItemGroupCmd(items, this);
        m_undoStack->push(groupCmd);
    } else {
        groupItems(items);
    }
}

GraphicsItem *ViewGraphics::groupItems(QList<GraphicsItem *> items)
{
    GraphicsItem *itemGroup = GraphicsItemManager::getInstance()->createGraphicsItemGroup(items);
    addItem(itemGroup);
    return itemGroup;
}

void ViewGraphics::ungroupItemsByCmd()
{
//    QList<GraphicsItem *> items = selectedItems();
    QList<GraphicsItem *> items;
    QList<GraphicsItem *> itemTempList = selectedItems();
    for (auto item : itemTempList) {
        if (item->subItem()->group()) {
            continue;
        }
        items << item;
    }

    if (items.isEmpty()) return;

    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemUngroupCmd *ungroupCmd = new ItemUngroupCmd(items, this);
        m_undoStack->push(ungroupCmd);
    } else {
        ungroupItems(items);
    }
}

void ViewGraphics::ungroupItems(QList<GraphicsItem *> items, bool isFreeMemory)
{
    qDebug() << "ungroupItems count:" << items.count();
    for (auto item : items) {
        if (item->type() != GraphicsItemType::GroupItem) continue;

        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        GraphicsItemGroup *parentGroup = itemGroup->itemGroup();
        for (auto childItem : itemGroup->getChildItems()) {
//            this->setZValue(childItem, -1);
            itemGroup->removeFromGroup(childItem);
            childItem->setItemGroup(nullptr);
            m_selectionManager->show(childItem);
            m_selectionManager->updateHandle(childItem);

            if (parentGroup) {
                parentGroup->addToGroup(childItem);
            }
        }

        this->deleteItem(item, isFreeMemory);
    }
}

void ViewGraphics::onAttributeValueChanged(AttributeBase *attribute, const QVariant &value, bool cmd)
{
    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled && cmd) {
        ItemAttributeChangedCmd *itemAttrChangedCmd =
            new ItemAttributeChangedCmd(attribute, value, this, true);
        m_undoStack->push(itemAttrChangedCmd);
    }
}

void ViewGraphics::duplicateItemsByCmd()
{
    QList<GraphicsItem *> items = selectedItems();
    qDebug() << "duplicateItems count:" << items.count();
    if (items.isEmpty()) return;

    m_modified = true;
    emit changed();

    if (m_isUndoCmdEnabled) {
        ItemCopyCmd *copyCmd = new ItemCopyCmd(items, this);
        m_undoStack->push(copyCmd);
    } else {
        duplicateItems(items);
    }
}

QList<GraphicsItem *> ViewGraphics::duplicateItems(QList<GraphicsItem *> items)
{
    QList<GraphicsItem *> itemCopyList;
    for (auto item : items) {
        GraphicsItem *itemCopy = item->duplicate();
        addItem(itemCopy);
        itemCopyList << itemCopy;
    }

    return itemCopyList;
}

QString ViewGraphics::getItemDisplayName(GraphicsItemType type)
{
    return GraphicsItemManager::getInstance()->getItemDisplayName(type);
}


void ViewGraphics::addItem(GraphicsItem *item)
{
    addGroupItems(item);
//    setZValue(item, 1);
//    GraphicsItemGroup *group = item->itemGroup();
//    if (group) {
//        group->addToGroup(item);
//    } else {
//        m_scene->addItem(item);
//    }
    m_scene->addItem(item);

}

void ViewGraphics::addGroupItems(GraphicsItem *item)
{
    //递归添加组的子图元
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        for (auto childItem : itemGroup->getChildItems()) {
//            childItem->setItemParent(item);
            addGroupItems(childItem);
//            m_selectionManager->hide(childItem, true);
        }
    }

//    if (item->subItem()->parentItem()) {
//        m_selectionManager->setZValue(item, m_selectionManager->zValue(item) + 1);
//    }
    addItemToSelectionManager(item);
    GraphicsItemManager::getInstance()->addItem(item);
//    qDebug() << "=========== itemCount:" << GraphicsItemManager::getInstance()->itemCount();
}

//void ViewGraphics::setZValue(GraphicsItem *item, int increment)
//{
//    if (item->type() == GraphicsItemType::GroupItem) {
//        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
//        foreach (auto childItem, itemGroup->getChildItems()) {
//            setZValue(childItem, increment);
//        }
//    }

//    if (item->subItem()->parentItem()) {
//        m_selectionManager->setZValue(item, m_selectionManager->zValue(item) + increment);
//    }
//}

void ViewGraphics::removeItem(GraphicsItem *item)
{
    if (item->type() == GraphicsItemType::GroupItem) {
        GraphicsItemGroup *itemGroup = dynamic_cast<GraphicsItemGroup *>(item);
        for (auto childItem : itemGroup->getChildItems()) {
            removeItem(childItem);
        }
    }

//    if (item->subItem()->parentItem()) {
//        m_selectionManager->setZValue(item, m_selectionManager->zValue(item) - 1);
//    }
    m_selectionManager->removeItem(item);
    GraphicsItemManager::getInstance()->removeItem(item->uid());
}

QAction *ViewGraphics::createUndoAction()
{
    QAction *undoAct = m_undoStack->createUndoAction(this, tr("Undo"));
    undoAct->setIcon(QIcon(":/icons/undo.png"));
    return undoAct;
}

QAction *ViewGraphics::createRedoAction()
{
    QAction *redo = m_undoStack->createRedoAction(this, tr("Redo"));
    redo->setIcon(QIcon(":/icons/redo.png"));
    return redo;
}

bool ViewGraphics::canUndo() const
{
    bool isCanUndo = m_undoStack->canUndo();
//    if (isCanUndo) {
//        m_modified = false;
//    }
    return isCanUndo;
}

bool ViewGraphics::canRedo() const
{
    return m_undoStack->canRedo();
}

void ViewGraphics::addItemToSelectionManager(GraphicsItem *item)
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
    return m_undoStack;
}

bool ViewGraphics::isControlModifier() const
{
    return m_scene->isControlModifier();
}

void ViewGraphics::setIsControlModifier(bool newIsControlModifier)
{
    m_scene->setIsControlModifier(newIsControlModifier);
}


QList<GraphicsItem *> ViewGraphics::selectedItems()
{
    QList<GraphicsItem *> selectedItemList;

    QList<QGraphicsItem *> items = m_scene->selectedItems();
    for (auto item : items) {
        GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
        if (handle->handleType() == GraphicsHandle::Drag) {
            selectedItemList << handle->item();
        }
    }

    return selectedItemList;
}

void ViewGraphics::wheelEvent(QWheelEvent *wheelEvent)
{
    if (wheelEvent->modifiers() == Qt::ControlModifier) {
        int degree = wheelEvent->angleDelta().y() / 8;
        QPoint zoomOrigin = wheelEvent->position().toPoint();
        if (degree > 0)
            emit zoomIn(zoomOrigin);
        else if (degree < 0)
            emit zoomOut(zoomOrigin);
    }
}

QList<GraphicsItem *> ViewGraphics::items()
{
    QList<GraphicsItem *> itemList;

    QSet<GraphicsItem *> items = m_scene->itemSet();
    for (auto item : items) {
        if (item->itemGroup() == nullptr) {
            itemList << item;
        }
    }

    return itemList;
}

//QList<GraphicsItem *> ViewGraphics::items()
//{
//    QList<GraphicsItem *> itemList;

//    QList<QGraphicsItem *> items = m_scene->items();
//    for (auto item : items) {
//        GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
//        if (handle->handleType() == GraphicsHandle::Drag) {
//            GraphicsItem *item = handle->item();
//            if (item->itemGroup() == nullptr) {
//                itemList << item;
//            }
//        }
//    }

//    return itemList;
//}
void ViewGraphics::cleanAllSelected()
{
    auto items = m_scene->selectedItems();
    for (auto item : items) {
        item->setSelected(false);
    }
}

QPointF ViewGraphics::opposite(GraphicsItem *item, int handleType) const
{
    return m_selectionManager->opposite(item, handleType);
}

void ViewGraphics::updateHandle(GraphicsItem *item)
{
    m_selectionManager->updateHandle(item);
}

NodeBase* ViewGraphics::getCurrentSelectedNode()
{
    QList<GraphicsItem*> items = selectedItems();
    if (items.size() == 1)
    {
        GraphicsItem* canvasItem = items.first();
        if (canvasItem == nullptr)
            return nullptr;

        return canvasItem->getCurrentNode();
    }

    return m_scene->getCurrentNode();
}

void ViewGraphics::setModified(bool value)
{
    m_modified = value;
}

bool ViewGraphics::isModified() const
{
    return m_modified;
}

bool ViewGraphics::save()
{

}

bool ViewGraphics::saveAs()
{

}

bool ViewGraphics::saveFile(QString *errorString, const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        *errorString = tr("Could not open file:") + fileName + tr("\nfor writing:") + file.errorString() + ".";
        return false;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
//    xml.writeDTD("<!DOCTYPE GraphicsView>");
    xml.writeStartElement(CANVAS);
    m_scene->getCurrentNode()->saveToXml(&xml);
    for (auto item : items()) {
        item->saveToXml(&xml);
    }
    xml.writeEndElement();
    xml.writeEndDocument();
    return true;
}

bool ViewGraphics::loadFile(QString *errorString, const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        *errorString = tr("Could not open file :") + fileName + tr("\nfor reading:") + file.errorString() + ".";
        return false;
    }

    if (file.size() == 0) {
        return true;
    }

    QXmlStreamReader xml(&file);
    if (xml.readNextStartElement()) {
        if ( xml.name().toString() == QString::fromUtf8(CANVAS) ) {
            qreal width = xml.attributes().value(WIDTH).toDouble();
            qreal height = xml.attributes().value(HEIGHT).toDouble();
            m_scene->getCurrentNode()->getAttribute(QString::fromUtf8(WIDTH))->setValue(width);
            m_scene->getCurrentNode()->getAttribute(QString::fromUtf8(HEIGHT))->setValue(height);
            GraphicsItemManager::getInstance()->loadGraphicsItem(&xml);
        }
    }

//    setCurrentFile(fileName);
    if (xml.error()) {
        *errorString = xml.errorString();
    }

    return !xml.error();
}

//void ViewGraphics::loadCanvas(QXmlStreamReader *xml)
//{
//    Q_ASSERT(xml->isStartElement() && xml->name() == "canvas");

//    while (xml->readNextStartElement()) {
//        GraphicsItem *item = NULL;
//        if (xml->name() == tr("rect")) {
//            item = new GraphicsRectItem(QRectF(0, 0, 100, 100));
//        }else if (xml->name() == tr("roundrect")) {
//            item = new GraphicsRectItem(QRect(0,0,1,1),true);
//        else if ( xml->name() == tr("group")) {
////            item =qgraphicsitem_cast<AbstractShape*>(loadGroupFromXML(xml));
//        }
//        else {
//            xml->skipCurrentElement();
//        }

//        if (item && item->loadFromXml(xml))
//            scene()->addItem(item);
//        else if ( item )
//            delete item;
//    }
//}
//void ViewGraphics::createTextItem()
//{
//    GraphicsItem *textItem = GraphicsItemManager::getInstance()->createGraphicsItem(GraphicsItemManager::TextItem);
//    addItemToScene(textItem);
//}

//void ViewGraphics::createRectItem()
//{
//    GraphicsItem *rectItem = GraphicsItemManager::getInstance()->createGraphicsItem(GraphicsItemManager::RectItem);
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
//    m_selectionManager->updateHandle(item);
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
