#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "scenegraphics.h"
//#include "canvasbarcodeitem.h"
//#include "decoratoritemgraphics.h"
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
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

    //多选功能
    connect(m_selectAct, &QAction::triggered, this, [this]() {
        qDebug() << "checked:" << m_selectAct->isChecked();
        ui->graphicsView->setIsControlModifier(m_selectAct->isChecked());
    });

    //拷贝功能
    m_copyAct = new QAction(QIcon(":/icons/copy"), tr("copy"));
    connect(m_copyAct, &QAction::triggered, this, [this]() {
        ui->graphicsView->duplicateItems();
    });

    //删除功能
    m_deleteAct = new QAction(QIcon(":/icons/delete"), tr("delete"));
    connect(m_deleteAct, &QAction::triggered, this, [this]() {
        ui->graphicsView->deleteItems();
    });

    ui->editToolBar->addAction(m_undoAct);
    ui->editToolBar->addAction(m_redoAct);
    ui->editToolBar->addSeparator();
    ui->editToolBar->addAction(m_selectAct);
    ui->editToolBar->addAction(m_copyAct);
    ui->editToolBar->addAction(m_deleteAct);
    ui->editToolBar->addSeparator();
    ui->editToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->undoView->setStack(ui->graphicsView->getUndoStack());
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


void MainWindow::on_shpeBtn_clicked()
{
    ui->graphicsView->createItem(GraphicsItemType::RectItem);
}


void MainWindow::on_textBtn_clicked()
{
    ui->graphicsView->createItem(GraphicsItemType::TextItem);
}


void MainWindow::on_barcodeBtn_clicked()
{
    ui->graphicsView->createItem(GraphicsItemType::BarcodeItem);
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
}

void MainWindow::on_pushButton_clicked()
{

}

