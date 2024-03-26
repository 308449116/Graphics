#include "customintspinbox.h"
#include <QKeyEvent>

CustomIntSpinBox::CustomIntSpinBox(QWidget *parent)
    :QSpinBox(parent)
{

}

CustomIntSpinBox::~CustomIntSpinBox()
{

}

QSize CustomIntSpinBox::sizeHint() const
{
    QSize size(80, 30);
    return size;
}

void CustomIntSpinBox::keyPressEvent(QKeyEvent *event)
{
    QSpinBox::keyPressEvent(event);
    event->accept();
}
