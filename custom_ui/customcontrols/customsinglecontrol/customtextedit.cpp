#include "customtextedit.h"
#include <QKeyEvent>
#include <QDebug>

CustomTextEdit::CustomTextEdit(QWidget *parent)
    :QTextEdit(parent)
{

}

CustomTextEdit::~CustomTextEdit()
{

}

void CustomTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Enter)
    {
        emit pressedEnterKey();
        event->accept();
        return;
    }

    return QTextEdit::keyPressEvent(event);
}

QSize CustomTextEdit::sizeHint() const
{
    QSize size(80, 180);
    return size;
}
