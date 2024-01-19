#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SceneGraphics;
class QGraphicsSimpleTextItem;
class CanvasTextItem;
class GraphicsItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_shpeBtn_clicked();

    void on_textBtn_clicked();

    void on_barcodeBtn_clicked();

    void on_underLineBtn_clicked(bool checked);
    void on_imageBtn_clicked();

private:
    Ui::MainWindow* ui;
    SceneGraphics* m_scene;
    CanvasTextItem* textItem;
    QGraphicsSimpleTextItem *textitem2;
    GraphicsItem *rectItem;
    int angle = 90;
};
#endif // MAINWINDOW_H
