#include "customwidget.h"
//#include "CustomCore/customstyleconfig.h"
#include <QStyleOption>
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent)
    :QWidget(parent)
{
//    g_StyleConfig->setCurrentStyle(this, "DefaultWidget");
}

CustomWidget::~CustomWidget()
{

}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    customPaint(&p);
    return QWidget::paintEvent(event);
}

void CustomWidget::customPaint(QPainter *painter)
{

}
