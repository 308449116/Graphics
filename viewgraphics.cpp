#include "viewgraphics.h"
//#include "graphicshandle.h"
#include "graphicsselection.h"
#include <QMouseEvent>
#include "scenegraphics.h"
#include "graphicsrectitem.h"
//#include "canvastextitem.h"

// ------------------------ ViewGraphics::Selection
// Maintains a pool of GraphicsSelection to be used for selected item.

class ViewGraphics::Selection
{
    Q_DISABLE_COPY_MOVE(Selection)
public:
    Selection();

    ~Selection();

    // Clear
    void clear();

    // Also clear out the pool. Call if reparenting of the main container occurs.
    void  clearSelectionPool();

    bool isItemSelected(GraphicsItem *item) const;

    QList<GraphicsItem *> selectedItems() const;

    GraphicsSelection *addItem(QGraphicsScene *scene, GraphicsItem *item);

    // remove widget, return new current widget or 0
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

ViewGraphics::Selection::Selection() = default;

ViewGraphics::Selection::~Selection()
{
    clearSelectionPool();
}

void ViewGraphics::Selection::clear()
{
    if (!m_usedSelections.isEmpty()) {
        for (auto it = m_usedSelections.begin(), mend = m_usedSelections.end(); it != mend; ++it)
            it.value()->setItem(nullptr);
        m_usedSelections.clear();
    }
}

void  ViewGraphics::Selection::clearSelectionPool()
{
    clear();
    qDeleteAll(m_selectionPool);
    m_selectionPool.clear();
}

GraphicsSelection *ViewGraphics::Selection::addItem(QGraphicsScene *scene, GraphicsItem *item)
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
    qDebug() << "m_selectionPool count:" << m_selectionPool.count();
    qDebug() << "m_usedSelections count:" << m_usedSelections.count();
    return gs;
}

GraphicsItem* ViewGraphics::Selection::removeItem(GraphicsItem *item)
{
    GraphicsSelection *s = m_usedSelections.value(item);
    if (!s)
        return item;

    s->setItem(nullptr);
    m_usedSelections.remove(item);

    if (m_usedSelections.isEmpty())
        return nullptr;

    return (*m_usedSelections.begin())->item();
}

bool ViewGraphics::Selection::isItemSelected(GraphicsItem *item) const{
    return  m_usedSelections.contains(item);
}

QList<GraphicsItem *> ViewGraphics::Selection::selectedItems() const
{
    return m_usedSelections.keys();
}

void ViewGraphics::Selection::updateGeometry(GraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->updateGeometry();
    }
}

void ViewGraphics::Selection::hide(GraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        qDebug() << "Selection hide";
        s->hide();
    }
}

void ViewGraphics::Selection::show(GraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item))
        s->show();
}

int ViewGraphics::Selection::collidesWithHandle(GraphicsItem *item, const QPointF &point) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->collidesWithHandle(point);
    }

    return 0;
}

QPointF ViewGraphics::Selection::opposite(GraphicsItem *item, int handleType) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->opposite(handleType);
    }

    return QPointF();
}











//========================================================================================
ViewGraphics::ViewGraphics(QWidget* parent)
    : QGraphicsView{parent}, m_selection(new Selection)
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
    connect(m_scene, &SceneGraphics::deleteGraphicsItem, this, &ViewGraphics::removeItemFormScene);
    connect(m_scene, &SceneGraphics::handleStateChange, this, &ViewGraphics::handleStateSwitch);
    connect(m_scene, &SceneGraphics::updateItemHandle, this, &ViewGraphics::updateItemHandle);
}

ViewGraphics::~ViewGraphics()
{
    delete m_selection;
    m_scene->deleteLater();
}

void ViewGraphics::createTextItem()
{
//    QFont font;
//    font.setPixelSize(100);
//    CanvasTextItem *textItem = new CanvasTextItem();
//    //    textitem2 = new QGraphicsSimpleTextItem("jpkD");
//    //    textitem2->setFont(font);
//    //    textitem2->setFlags(GraphicsItem::ItemIsSelectable |
//    //                        GraphicsItem::ItemIsMovable);
//    //    textitem2->setPos(textItem->pos());
//    qDebug() << "textItem->pos"<< textItem->pos();
//    //    qDebug() << "textitem2->pos"<< textitem2->pos();
//    //    textItem->setCurrentText("123");
//    //    textItem->setCurrentFont(font);
//    //    RectGrabber* gabber = new RectGrabber(QSizeF(8, 8));
//    //    DecoratorItemGraphics* item = new DecoratorItemGraphics(rectItem, gabber);
//    m_scene->addItem(textItem);
//    m_manageItem.insert(textItem);
//    //    m_scene->addItem(textitem2);
}

void ViewGraphics::createRectItem()
{
    GraphicsRectItem *rectItem = new GraphicsRectItem(QRectF(0, 0, 100, 100));
    addItemToScene(rectItem);
    /*
    //    CanvasRectItem* rectItem = new CanvasRectItem();
    //    rectItem->setSize(100, 100);
    //    rectItem->setFlag(GraphicsItem::ItemIsSelectable, false);
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 100, 100));
    rectItem->setFlag(GraphicsItem::ItemIsSelectable, true);
    rectItem->setFlag(GraphicsItem::ItemIsMovable, true);
    //    CanvasRectItem* rectItem2 = new CanvasRectItem();
    //    rectItem2->setSize(100, 100);
    //    rectItem2->setPos(110, 0);
    //    rectItem2->setFlag(GraphicsItem::ItemIsSelectable, false);
    //    rectItem2->setSelected(false);

    //    QGraphicsItemGroup *group = new QGraphicsItemGroup();
    //    group->setFlags(GraphicsItem::ItemIsMovable |
    //                    GraphicsItem::ItemIsSelectable);
    //    group->addToGroup(rectItem);
    //    group->addToGroup(rectItem2);
    //    RectGrabber* gabber = new RectGrabber(QSizeF(8, 8));
    //    DecoratorItemGraphics* item = new DecoratorItemGraphics(rectItem, gabber);
    m_scene->addItem(rectItem);
    m_manageItem.insert(rectItem);
    */
}

void ViewGraphics::createBarcoedItem()
{
//    CanvasBarcodeItem *barcodeitem = new CanvasBarcodeItem();
//    m_scene->addItem(barcodeitem);
//    m_manageItem.insert(barcodeitem);
}

bool ViewGraphics::isManaged(GraphicsItem *item)
{
    return m_manageItem.contains(item);
}

void ViewGraphics::manageItem(GraphicsItem *item)
{
    m_manageItem.insert(item);
}

void ViewGraphics::unmanageItem(GraphicsItem *item)
{
    m_manageItem.remove(item);
}

int ViewGraphics::collidesWithHandle(GraphicsItem *item, const QPointF &point) const
{
    return m_selection->collidesWithHandle(item, point);
}

void ViewGraphics::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动事件
//    QPoint point = event->pos();      //QGraphicsView的坐标
    QGraphicsView::mouseMoveEvent(event);
}

void ViewGraphics::mousePressEvent(QMouseEvent *event)
{
    /*
    //鼠标左键按下事件
    if ( event->button() != Qt::LeftButton ) return;

    QPoint point = event->pos();  //QGraphicsView的坐标
    QPointF pointScene = this->mapToScene(point);         //转换到Scene坐标
    GraphicsItem *currentItem = m_scene->itemAt(pointScene, this->transform());   //获取光标下的绘图项

    if (m_currentItem) {

    } else {
        if (currentItem != nullptr) {
            if (trySelectItem(currentItem)) {
            } else {
            }
        } else {
            m_selection->hide(currentItem);
        }
    }
    QList<GraphicsItem  *> listItem = m_scene->selectedItems();
    qDebug() << "selectedItems count:" << listItem.count();
    qDebug() << "items count:" << m_scene->items().count();
    if (currentItem != nullptr) {
        if (m_selection->isItemSelected(currentItem)) {
            m_selection->show(currentItem);
        } else {
            m_selection->addItem(m_scene, currentItem);
        }
    } else {
        m_selection->hide(currentItem);
    }

    foreach (GraphicsItem  *item, listItem) {
        qDebug() << "222222222";

//        if (currentItem != nullptr) {
//            qDebug() << "3333333";
//            //                if (!isManaged(currentItem) && !isCentralWidget(currentItem))
//            //                    return ;
//            if (m_selection->isItemSelected(item)) {
//                qDebug() << "44444444444";

//                m_selection->show(item);
//                //                    qDebug() << "item pos:" << QString::asprintf("Item 坐标：%.0f,%.0f", currentItem.x(),currentItem.y());
//                qDebug() << "item pos:" << item->pos();
//                qDebug() << "item scenePos:" << item->scenePos();
//            } else {
//                qDebug() << "555555555";

//                m_selection->addItem(m_scene, item);
//            }
//        } else {
//            qDebug() << "6666666666666";

//            m_selection->hide(item);
//        }
    }
    */
    QGraphicsView::mousePressEvent(event);
}

void ViewGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

bool ViewGraphics::isItemSelected(GraphicsItem *item) const
{
    return m_selection->isItemSelected(item);
}

QPointF ViewGraphics::opposite(GraphicsItem *item, int handleType) const
{
    return m_selection->opposite(item, handleType);
}

bool ViewGraphics::trySelectItem(GraphicsItem *item)
{
    if (!isManaged(item)) {
        return false;
    }

    if (m_currentItem == item) {
        return true;
    }

    if (item) {
        if (m_selection->isItemSelected(item)) {
            m_selection->show(item);
        } else {
            m_selection->addItem(m_scene, item);
        }
    }

    m_selection->hide(m_currentItem);
    m_currentItem = item;
    return true;
}

void ViewGraphics::addItemToScene(GraphicsItem *item)
{
    m_scene->addItem(item);
    connect(item, &GraphicsItem::selectedChange, this, &ViewGraphics::selectedStateChange);
}

void ViewGraphics::selectedStateChange(GraphicsItem *item, bool checked)
{
    if (item == nullptr) return;

    if (!m_selection->isItemSelected(item)) {
        m_selection->addItem(m_scene, item);
        return;
    }

    if (checked) {
        m_selection->show(item);
    } else {
        m_selection->hide(item);
    }
}

void ViewGraphics::removeItemFormScene(GraphicsItem *item)
{
    if (item == nullptr) return;

    if (m_selection->isItemSelected(item)) {
        m_selection->removeItem(item);
    }
}

void ViewGraphics::updateItemHandle(GraphicsItem *item)
{
    m_selection->updateGeometry(item);
    m_selection->show(item);
}

void ViewGraphics::handleStateSwitch(GraphicsItem *item, bool isHide)
{
    qDebug() << "handleStateSwitch 1111111111 isHide:" << isHide;

    if (item == nullptr) return;

    if (isHide) {
        qDebug() << "handleStateSwitch 22222222 isHide:" << isHide;

        m_selection->hide(item);
    } else {
        qDebug() << "handleStateSwitch 33333333 isHide:" << isHide;

        m_selection->show(item);
    }
}
