#include "customcombobox.h"
#include <QListView>

CustomComboBox::CustomComboBox(QWidget *parent)
    :QComboBox(parent)
{
    this->setView(new QListView(this));
}

CustomComboBox::~CustomComboBox()
{

}

QSize CustomComboBox::sizeHint() const
{
    QSize size(80, 30);
    return size;
}
