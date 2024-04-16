#ifndef CUSTOMLINEEDITCONTROL_H
#define CUSTOMLINEEDITCONTROL_H

#include "customcombinecontrolbase.h"
#include "custom_ui/customcontrols/customsinglecontrol/customlineedit.h"
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>

class CustomLineEditControl : public CustomCombineControlBase
{
    Q_OBJECT

public:
    CustomLineEditControl(QWidget *parent = nullptr);
    ~CustomLineEditControl();

    // 设置按钮相关
    void setToolButtonVisible(bool isVisible);
    void setToolButtonText(const QString& text);
    void setToolButtonIcon(const QIcon& icon);

    // 设置文本
    void setText(const QString& string);
    QString getText();

    //设置控件是否使能
    void setEnabled(bool enabled);

signals:
    void clickedToolButton();
    void textChanged(const QString &text);
    void editingFinished();

private:
    CustomLineEdit *m_lineEdit = nullptr;
    QToolButton *m_toolButton = nullptr;
};

#endif
