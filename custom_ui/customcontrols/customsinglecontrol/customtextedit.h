#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QWidget>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    CustomTextEdit(QWidget *parent = nullptr);
    ~CustomTextEdit() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    QSize sizeHint() const override;

signals:
    void pressedEnterKey();         // 按下小回车时，发送此信号
};

#endif
