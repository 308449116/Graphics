#include "viewgraphics.h"
//#include "Handle/graphicshandle.h"
#include "Handle/graphicsselection.h"
#include <QGraphicsItem>
#include <QMouseEvent>
#include "GraphicsObject/scenegraphics.h"
#include "GraphicsObject/canvasrectitem.h"
#include "GraphicsObject/canvastextitem.h"

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

    bool isItemSelected(QGraphicsItem *item) const;

    QList<QGraphicsItem *> selectedItems() const;

    GraphicsSelection *addItem(QGraphicsScene *scene, QGraphicsItem *item);

    // remove widget, return new current widget or 0
    QGraphicsItem* removeItem(QGraphicsItem *item);

    void updateGeometry(QGraphicsItem *item);

    void hide(QGraphicsItem *item);

    void show(QGraphicsItem *item);

    int collidesWithHandle(QGraphicsItem *item, const QPointF & point) const;

    QPointF opposite(QGraphicsItem *item, int handleType) const;

private:

    using SelectionPool = QList<GraphicsSelection *>;

    SelectionPool m_selectionPool;

    QHash<QGraphicsItem *, GraphicsSelection *> m_usedSelections;
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

GraphicsSelection *ViewGraphics::Selection::addItem(QGraphicsScene *scene, QGraphicsItem *item)
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
    return gs;
}

QGraphicsItem* ViewGraphics::Selection::removeItem(QGraphicsItem *item)
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

bool ViewGraphics::Selection::isItemSelected(QGraphicsItem *item) const{
    return  m_usedSelections.contains(item);
}

QList<QGraphicsItem *> ViewGraphics::Selection::selectedItems() const
{
    return m_usedSelections.keys();
}

void ViewGraphics::Selection::updateGeometry(QGraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        s->updateGeometry();
    }
}

void ViewGraphics::Selection::hide(QGraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item))
        s->hide();
}

void ViewGraphics::Selection::show(QGraphicsItem *item)
{
    if (GraphicsSelection *s = m_usedSelections.value(item))
        s->show();
}

int ViewGraphics::Selection::collidesWithHandle(QGraphicsItem *item, const QPointF &point) const
{
    if (GraphicsSelection *s = m_usedSelections.value(item)) {
        return s->collidesWithHandle(point);
    }

    return 0;
}

QPointF ViewGraphics::Selection::opposite(QGraphicsItem *item, int handleType) const
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
    connect(m_scene, &SceneGraphics::deleteGraphicsItem, this, &ViewGraphics::unmanageItem);
}

ViewGraphics::~ViewGraphics()
{
    delete m_selection;
    m_scene->deleteLater();
}

void ViewGraphics::createTextItem()
{
    QFont font;
    font.setPixelSize(100);
    CanvasTextItem *textItem = new CanvasTextItem();
    //    textitem2 = new QGraphicsSimpleTextItem("jpkD");
    //    textitem2->setFont(font);
    //    textitem2->setFlags(QGraphicsItem::ItemIsSelectable |
    //                        QGraphicsItem::ItemIsMovable);
    //    textitem2->setPos(textItem->pos());
    qDebug() << "textItem->pos"<< textItem->pos();
    //    qDebug() << "textitem2->pos"<< textitem2->pos();
    //    textItem->setCurrentText("123");
    //    textItem->setCurrentFont(font);
    //    RectGrabber* gabber = new RectGrabber(QSizeF(8, 8));
    //    DecoratorItemGraphics* item = new DecoratorItemGraphics(rectItem, gabber);
    m_scene->addItem(textItem);
    m_manageItem.insert(textItem);

    //    m_scene->addItem(textitem2);
}

void ViewGraphics::createRectItem()
{
    //    CanvasRectItem* rectItem = new CanvasRectItem();
    //    rectItem->setSize(100, 100);
    //    rectItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 100, 100));
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    //    CanvasRectItem* rectItem2 = new CanvasRectItem();
    //    rectItem2->setSize(100, 100);
    //    rectItem2->setPos(110, 0);
    //    rectItem2->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //    rectItem2->setSelected(false);

    //    QGraphicsItemGroup *group = new QGraphicsItemGroup();
    //    group->setFlags(QGraphicsItem::ItemIsMovable |
    //                    QGraphicsItem::ItemIsSelectable);
    //    group->addToGroup(rectItem);
    //    group->addToGroup(rectItem2);
    //    RectGrabber* gabber = new RectGrabber(QSizeF(8, 8));
    //    DecoratorItemGraphics* item = new DecoratorItemGraphics(rectItem, gabber);
    m_scene->addItem(rectItem);
    m_manageItem.insert(rectItem);
}

void ViewGraphics::createBarcoedItem()
{
//    CanvasBarcodeItem *barcodeitem = new CanvasBarcodeItem();
//    m_scene->addItem(barcodeitem);
//    m_manageItem.insert(barcodeitem);
}

bool ViewGraphics::isManaged(QGraphicsItem *item)
{
    return m_manageItem.contains(item);
}

void ViewGraphics::manageItem(QGraphicsItem *item)
{
    m_manageItem.insert(item);
}

void ViewGraphics::unmanageItem(QGraphicsItem *item)
{
    m_manageItem.remove(item);
}

int ViewGraphics::collidesWithHandle(QGraphicsItem *item, const QPointF &point) const
{
}

void ViewGraphics::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动事件
    QPoint point = event->pos();      //QGraphicsView的坐标
    QGraphicsView::mouseMoveEvent(event);
}

void ViewGraphics::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下事件
    if ( event->button() != Qt::LeftButton ) return;

    QPoint point = event->pos();  //QGraphicsView的坐标
    QPointF pointScene = this->mapToScene(point);         //转换到Scene坐标
    QGraphicsItem *currentItem = m_scene->itemAt(pointScene, this->transform());   //获取光标下的绘图项

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
    QList<QGraphicsItem  *> listItem = m_scene->selectedItems();
    qDebug() << "selectedItems count:" << listItem.count();
    qDebug() << "items count:" << m_scene->items().count();
//    qDebug() << "isSelected:" << currentItem->isSelected();
    if (currentItem != nullptr) {
        qDebug() << "3333333";
        //                if (!isManaged(currentItem) && !isCentralWidget(currentItem))
        //                    return ;
        if (m_selection->isItemSelected(currentItem)) {
            qDebug() << "44444444444";

            m_selection->show(currentItem);
            //                    qDebug() << "item pos:" << QString::asprintf("Item 坐标：%.0f,%.0f", currentItem.x(),currentItem.y());
        } else {
            qDebug() << "555555555";

            m_selection->addItem(m_scene, currentItem);
        }
    } else {
        qDebug() << "6666666666666";

        m_selection->hide(currentItem);
    }

    foreach (QGraphicsItem  *item, listItem) {
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

    QGraphicsView::mousePressEvent(event);
}

void ViewGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isMousePress) {
//        m_isMousePress = false;

//        QPoint point = event->pos();  //QGraphicsView的坐标
//        QPointF pointScene = this->mapToScene(point);         //转换到Scene坐标
//        QGraphicsItem  *item=NULL;
//        item = m_scene->itemAt(pointScene, this->transform());   //获取光标下的绘图项
//        if (item != NULL) {
//            m_selection->addItem(m_scene, item);
//            QPointF pointItem = item->mapFromScene(pointScene);   //转换为绘图项的局部坐标
//            qDebug() << "item pos:" << QString::asprintf("Item 坐标：%.0f,%.0f", pointItem.x(),pointItem.y());
//            qDebug() << "item pos:" << item->pos();
//            qDebug() << "item scenePos:" << item->scenePos();
//        } else {
//            qDebug() << "Item 坐标：null, null";
//            m_selection->clear();
//        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

bool ViewGraphics::isItemSelected(QGraphicsItem *item) const
{
    return m_selection->isItemSelected(item);
}

QPointF ViewGraphics::opposite(QGraphicsItem *item, int handleType) const
{
    return m_selection->opposite(item, handleType);
}

bool ViewGraphics::trySelectItem(QGraphicsItem *item)
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
