#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "scenegraphics.h"
//#include "canvasbarcodeitem.h"
//#include "decoratoritemgraphics.h"
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_undoAct = ui->graphicsView->createUndoAction();
    m_redoAct = ui->graphicsView->createRedoAction();
    ui->editToolBar->addAction(m_undoAct);
    ui->editToolBar->addAction(m_redoAct);
    ui->editToolBar->addSeparator();
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
    ui->graphicsView->createItem(GraphicsItemManager::RectItem);
}


void MainWindow::on_textBtn_clicked()
{
    ui->graphicsView->createItem(GraphicsItemManager::TextItem);
}


void MainWindow::on_barcodeBtn_clicked()
{
    ui->graphicsView->createItem(GraphicsItemManager::BarcodeItem);
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

