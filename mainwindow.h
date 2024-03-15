#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QAction>
#include <QToolBar>
#include <QMainWindow>

class QUndoView;
class QScrollArea;
class SceneGraphics;
class UIAttributeWidget;
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

public slots:
    void onSelectedItemChanged();

    void on_shpeBtn_clicked();

    void on_textBtn_clicked();

    void on_barcodeBtn_clicked();

    void on_underLineBtn_clicked(bool checked);

    void updateActions();

private:
    Ui::MainWindow *ui;
    SceneGraphics *m_scene;
    QGraphicsSimpleTextItem *textitem2;
    QTimer m_timer;

    //action
    QAction *m_undoAct;
    QAction *m_redoAct;
    QAction *m_selectAct;
    QAction *m_copyAct;
    QAction *m_deleteAct;

    QAction *m_alignTopAct;
    QAction *m_alignBottomAct;
    QAction *m_alignLeftAct;
    QAction *m_alignRightAct;
    QAction *m_alignHCenterAct;
    QAction *m_alignVCenterAct;

    QAction *m_zoomInAct;
    QAction *m_zoomOutAct;

    QAction *m_groupAct;
    QAction *m_ungroupAct;
    // edit toolbar;
    QToolBar *m_editToolBar;

    // 属性界面
    UIAttributeWidget *m_pAttributeWidget = nullptr;
    QDockWidget *m_pAttributeDockWidget = nullptr;
//    QScrollArea *m_pScrollArea = nullptr;

    // Undo View
    QUndoView *m_pUndoView = nullptr;
    QDockWidget *m_pUndoViewDockWidget = nullptr;
};
#endif // MAINWINDOW_H
