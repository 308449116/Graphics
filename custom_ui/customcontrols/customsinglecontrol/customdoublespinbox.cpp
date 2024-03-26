#include "customdoublespinbox.h"
#include <QKeyEvent>

CustomDoubleSpinBox::CustomDoubleSpinBox(QWidget *parent)
    :QDoubleSpinBox(parent)
{

}

CustomDoubleSpinBox::~CustomDoubleSpinBox()
{

}

QSize CustomDoubleSpinBox::sizeHint() const
{
    QSize size(80, 30);
    return size;
}

void CustomDoubleSpinBox::keyPressEvent(QKeyEvent *event)
{
    QDoubleSpinBox::keyPressEvent(event);
    event->accept();
}
