#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "attributeview/attributewidget.h"
//#include "graphicsitemmanager.h"
//#include "graphicstextitem.h"
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QDockWidget>
#include <QUndoView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_selectAct = new QAction(QIcon(":/icons/select"), tr("select"));
    m_selectAct->setCheckable(true);

    //撤销功能
    m_undoAct = ui->graphicsView->createUndoAction();

    //重做功能
    m_redoAct = ui->graphicsView->createRedoAction();

    //放大功能
    m_zoomInAct = new QAction(QIcon(":/icons/zoomin"), tr("zoomIn"));
    connect(m_zoomInAct, &QAction::triggered, this, [this]() {
        ui->graphicsView->scale(1.2, 1.2);
    });

    //缩小功能
    m_zoomOutAct = new QAction(QIcon(":/icons/zoomout"), tr("zoomOut"));
    connect(m_zoomOutAct, &QAction::triggered, this, [this]() {
        ui->graphicsView->scale(1.0/1.2, 1.0/1.2);
    });

    //多选功能
    connect(m_selectAct, &QAction::triggered, this, [this]() {
        qDebug() << "checked:" << m_selectAct->isChecked();
        ui->graphicsView->setIsControlModifier(m_selectAct->isChecked());
    });

    //拷贝功能
    m_copyAct = new QAction(QIcon(":/icons/copy"), tr("copy"));
    connect(m_copyAct, &QAction::triggered, this, [this]() {
        ui->graphicsView->duplicateItemsByCmd();
    });

    //删除功能
    m_deleteAct = new QAction(QIcon(":/icons/delete"), tr("delete"));
    connect(m_deleteAct, &QAction::triggered, this, [this]() {
        ui->graphicsView->deleteItemsByCmd();
    });

    //上对齐
    m_alignTopAct = new QAction(QIcon(":/icons/align_top"), tr("align_top"));
    connect(m_alignTopAct, &QAction::triggered, this, [this](){
        ui->graphicsView->alignItems(AlignType::TOP_ALIGN);
    });

    //下对齐
    m_alignBottomAct = new QAction(QIcon(":/icons/align_bottom"), tr("align_bottom"));
    connect(m_alignBottomAct, &QAction::triggered, this, [this](){
        ui->graphicsView->alignItems(AlignType::BOTTOM_ALIGN);
    });

    //左对齐
    m_alignLeftAct = new QAction(QIcon(":/icons/align_left"), tr("align_left"));
    connect(m_alignLeftAct, &QAction::triggered, this, [this](){
        ui->graphicsView->alignItems(AlignType::LEFT_ALIGN);
    });

    //右对齐
    m_alignRightAct = new QAction(QIcon(":/icons/align_right"), tr("align_right"));
    connect(m_alignRightAct, &QAction::triggered, this, [this](){
        ui->graphicsView->alignItems(AlignType::RIGHT_ALIGN);
    });

    //水平对齐
    m_alignHCenterAct = new QAction(QIcon(":/icons/align_hcenter"), tr("align_hcenter"));
    connect(m_alignHCenterAct, &QAction::triggered, this, [this](){
        ui->graphicsView->alignItems(AlignType::HCENTER_ALIGN);
    });

    //垂直对齐
    m_alignVCenterAct = new QAction(QIcon(":/icons/align_vcenter"), tr("align_vcenter"));
    connect(m_alignVCenterAct, &QAction::triggered, this, [this](){
        ui->graphicsView->alignItems(AlignType::VCENTER_ALIGN);
    });

    //创建组
    m_groupAct = new QAction(QIcon(":/icons/group"), tr("group"));
    connect(m_groupAct, &QAction::triggered, this, [this](){
        ui->graphicsView->groupItemsByCmd();
    });

    //取消组
    m_ungroupAct = new QAction(QIcon(":/icons/ungroup"), tr("ungroup"));
    connect(m_ungroupAct, &QAction::triggered, this, [this](){
        ui->graphicsView->ungroupItemsByCmd();
    });

    ui->editToolBar->addAction(m_undoAct);
    ui->editToolBar->addAction(m_redoAct);
    ui->editToolBar->addSeparator();

    ui->editToolBar->addAction(m_zoomInAct);
    ui->editToolBar->addAction(m_zoomOutAct);
    ui->editToolBar->addSeparator();

    ui->editToolBar->addAction(m_selectAct);
    ui->editToolBar->addAction(m_copyAct);
    ui->editToolBar->addAction(m_deleteAct);
    ui->editToolBar->addSeparator();

    ui->editToolBar->addAction(m_alignTopAct);
    ui->editToolBar->addAction(m_alignBottomAct);
    ui->editToolBar->addAction(m_alignLeftAct);
    ui->editToolBar->addAction(m_alignRightAct);
    ui->editToolBar->addAction(m_alignHCenterAct);
    ui->editToolBar->addAction(m_alignVCenterAct);
    ui->editToolBar->addSeparator();

    ui->editToolBar->addAction(m_groupAct);
    ui->editToolBar->addAction(m_ungroupAct);
    ui->editToolBar->addSeparator();

    ui->editToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //    ui->undoView->setStack(ui->graphicsView->getUndoStack());
    // 添加属性界面

    m_pAttributeDockWidget = new QDockWidget(tr("Attribute"));
    m_pAttributeDockWidget->setFeatures(QDockWidget::DockWidgetMovable |
                                        QDockWidget::DockWidgetClosable);
    m_pAttributeDockWidget->setFloating(true);
    m_pAttributeWidget = new AttributeWidget;
    //    m_pScrollArea = new QScrollArea;
    //    scrollArea->setBackgroundRole(QPalette::Dark);
    //    m_pScrollArea->setWidget(m_pAttributeWidget);
    m_pAttributeDockWidget->setWidget(m_pAttributeWidget);
    this->addDockWidget(Qt::RightDockWidgetArea, m_pAttributeDockWidget);

    // Undo View
    m_pUndoViewDockWidget = new QDockWidget(tr("UndoStack"));
    m_pUndoViewDockWidget->setFeatures(QDockWidget::DockWidgetMovable |
                                       QDockWidget::DockWidgetClosable);
    m_pUndoViewDockWidget->setFloating(true);
    m_pUndoView = new QUndoView(ui->graphicsView->getUndoStack());
    m_pUndoViewDockWidget->setWidget(m_pUndoView);
    this->addDockWidget(Qt::RightDockWidgetArea, m_pUndoViewDockWidget);

    QObject::connect(ui->graphicsView, &ViewGraphics::itemSelectedChanged, \
                     this, &MainWindow::onSelectedItemChanged);

    updateActions();
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::updateActions);
    m_timer.start(1000);
    //    int width = 600;
    //    int height = 400;
    //    QRectF rect(-width/2, -height/2, width, height);
    //    QRectF rect(0, 0, width, height);
    //    m_scene = new SceneGraphics(this);
    //    m_scene->setSceneRect(rect);
    //    m_scene = dynamic_cast<SceneGraphics*>(ui->graphicsView->scene());
    //    if (!m_scene) {
    //        qDebug("=============");
    //    }
    //    QGraphicsTextItem * testitem = new QGraphicsTextItem("test");
    //    QGraphicsItem * item = qgraphicsitem_cast<QGraphicsItem *>(testitem);
    //    m_scene->addItem(item);

    //    QGraphicsRectItem *rectItem = new QGraphicsRectItem(rect);
    //    rectItem->setFlags(QGraphicsItem::ItemIsSelectable |
    //                       QGraphicsItem::ItemSendsGeometryChanges);

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

    //    qDebug() << "ui->graphicsView->rect"<< ui->graphicsView->rect();
    //    ui->graphicsView->setScene(m_scene);
    //    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //    ui->graphicsView->setGeometry(0, 0, width, height);
    //    qDebug() << "ui->graphicsView->geometry:"<< ui->graphicsView->geometry();
    //    qDebug() << "ui->graphicsView->pos:"<< ui->graphicsView->pos();

    //    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    //    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    //    ui->graphicsView->setCursor(QCursor());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_shapeBtn_clicked()
{
    ui->graphicsView->createItemByCmd(GraphicsItemType::RectItem);
}


void MainWindow::on_textBtn_clicked()
{
    ui->graphicsView->createItemByCmd(GraphicsItemType::TextItem);
}


void MainWindow::on_barcodeBtn_clicked()
{
    QGraphicsRectItem *rect1 = new QGraphicsRectItem(QRectF(0, 0, 100, 100));
    QGraphicsRectItem *rect2 = new QGraphicsRectItem(QRectF(200, 200, 100, 100));
    rect1->setPos(200, 200);
    rect1->setTransformOriginPoint(rect1->boundingRect().center());
    rect1->setRotation(30);
    QGraphicsItemGroup* group = new QGraphicsItemGroup();
    group->addToGroup(rect1);
    group->addToGroup(rect2);
    ui->graphicsView->scene()->addItem(group);


    group->removeFromGroup(rect1);
    group->removeFromGroup(rect2);
    rect1->setRotation(0);
    //    rect1->moveBy(-200, -200);
    rect1->setPos(0, 0);
    //    GraphicsItem *item =
    //        GraphicsItem *( new GraphicsTextItem("jkpg") );
    //    ui->graphicsView->scene()->addItem(item);
    ;

    //    ui->graphicsView->createItemByCmd(GraphicsItemType::BarcodeItem);
}

void MainWindow::on_underLineBtn_clicked(bool checked)
{
    //    qDebug() << "checked:"<< checked;
    //    QFont font = textItem->getCurrentFont();
    //    font.setUnderline(true);
    //    font.setOverline(true);
    //    font.setItalic(true);
    //    font.setStrikeOut(true);
    //    font.setBold(true);
    //    textItem->setCurrentFont(font);
}

void MainWindow::updateActions()
{
    m_undoAct->setEnabled(ui->graphicsView->canUndo());
    m_redoAct->setEnabled(ui->graphicsView->canRedo());

    m_copyAct->setEnabled(ui->graphicsView->selectedItems().count() >= 1);
    m_deleteAct->setEnabled(ui->graphicsView->selectedItems().count() >= 1);

    m_alignTopAct->setEnabled(ui->graphicsView->selectedItems().count() > 1);
    m_alignBottomAct->setEnabled(ui->graphicsView->selectedItems().count() > 1);
    m_alignLeftAct->setEnabled(ui->graphicsView->selectedItems().count() > 1);
    m_alignRightAct->setEnabled(ui->graphicsView->selectedItems().count() > 1);
    m_alignHCenterAct->setEnabled(ui->graphicsView->selectedItems().count() > 1);
    m_alignVCenterAct->setEnabled(ui->graphicsView->selectedItems().count() > 1);
}

void MainWindow::onSelectedItemChanged()
{
    NodeBase* node = ui->graphicsView->getCurrentSelectedNode();
    m_pAttributeWidget->setCurrentAttrNode(node);
}
