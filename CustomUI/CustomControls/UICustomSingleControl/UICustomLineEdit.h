#ifndef UICUSTOMLINEEDIT_H
#define UICUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QWidget>
#include "UICustomWidgtes/CustomWidget.h"

class UICustomCloseButton;
class UICustomLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    UICustomLineEdit(QWidget *parent = nullptr);
    ~UICustomLineEdit() override;

    // Close Button Visible
    void setCloseButtonEnable(bool isEnabled);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    UICustomCloseButton *m_pButton = nullptr;
    bool m_isToolButtonEnable = false;

signals:
    void currentTextChanged(const QString& text);

private slots:
    void onTextChanged(const QString& textChanged);
    void onCloseButtonClicked();
};

// ==============================================================
class UICustomCloseButton : public CustomWidget
{
    Q_OBJECT

public:
    UICustomCloseButton(QWidget *parent = nullptr);
    ~UICustomCloseButton();

protected:
    void customPaint(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void clicked();

private:
    bool m_isHoveredOn = false;
};

#endif
