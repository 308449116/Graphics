#ifndef UICUSTOMTEXTEDIT_H
#define UICUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QWidget>

class UICustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    UICustomTextEdit(QWidget* parent = nullptr);
    ~UICustomTextEdit() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    QSize sizeHint() const override;

signals:
    void pressedEnterKey();         // 按下小回车时，发送此信号
};

#endif
