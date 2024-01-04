#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QAction>
#include <QToolBar>
#include <QMainWindow>

class SceneGraphics;
class CanvasTextItem;
class QGraphicsSimpleTextItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_shpeBtn_clicked();

    void on_textBtn_clicked();

    void on_barcodeBtn_clicked();

    void on_underLineBtn_clicked(bool checked);

    void updateActions();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SceneGraphics *m_scene;
    CanvasTextItem *textItem;
    QGraphicsSimpleTextItem *textitem2;
    QTimer m_timer;

    // edit action
    QAction *m_undoAct;
    QAction *m_redoAct;
    QAction *m_selectAct;
    QAction *m_copyAct;
    QAction *m_deleteAct;

    // edit toolbar;
    QToolBar *m_editToolBar;
};
#endif // MAINWINDOW_H
