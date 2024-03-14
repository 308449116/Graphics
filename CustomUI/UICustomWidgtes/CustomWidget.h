#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    CustomWidget(QWidget* parent = nullptr);
    ~CustomWidget();

protected:
    void paintEvent(QPaintEvent* event) final;

    // Custom Paint Event
    virtual void customPaint(QPainter* painter);
};

#endif
