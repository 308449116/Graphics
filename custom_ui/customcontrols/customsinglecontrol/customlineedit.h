#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QWidget>
#include "custom_ui/customwidgtes/customwidget.h"

class CustomCloseButton;
class CustomLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CustomLineEdit(QWidget *parent = nullptr);
    ~CustomLineEdit() override;

    // Close Button Visible
    void setCloseButtonEnable(bool isEnabled);

protected:
//    void keyPressEvent(QKeyEvent *event) override;

private:
    CustomCloseButton *m_pButton = nullptr;
    bool m_isToolButtonEnable = false;

signals:
    void currentTextChanged(const QString& text);

private slots:
    void onTextChanged(const QString& textChanged);
    void onCloseButtonClicked();
};

// ==============================================================
class CustomCloseButton : public CustomWidget
{
    Q_OBJECT

public:
    CustomCloseButton(QWidget *parent = nullptr);
    ~CustomCloseButton();

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
