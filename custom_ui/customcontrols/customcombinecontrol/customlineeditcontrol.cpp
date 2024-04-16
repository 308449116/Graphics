#include "customlineeditcontrol.h"

CustomLineEditControl::CustomLineEditControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_lineEdit = new CustomLineEdit;
    m_mainLayout->addWidget(m_lineEdit);
    m_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_toolButton = new QToolButton;
    m_mainLayout->addWidget(m_toolButton);

    QObject::connect(m_lineEdit, &QLineEdit::textChanged, this, &CustomLineEditControl::textChanged);
    QObject::connect(m_lineEdit, &QLineEdit::editingFinished, this, &CustomLineEditControl::editingFinished);
    QObject::connect(m_toolButton, &QToolButton::clicked, this, &CustomLineEditControl::clickedToolButton);

    this->setWidth(400);
    this->setHeight(30);
}

CustomLineEditControl::~CustomLineEditControl()
{

}

void CustomLineEditControl::setToolButtonVisible(bool isVisible)
{
    m_toolButton->setVisible(isVisible);
}

void CustomLineEditControl::setToolButtonText(const QString& text)
{
    m_toolButton->setText(text);
}

void CustomLineEditControl::setToolButtonIcon(const QIcon& icon)
{
    m_toolButton->setIcon(icon);
}

void CustomLineEditControl::setText(const QString& string)
{
    m_lineEdit->setText(string);
}

QString CustomLineEditControl::getText()
{
    return m_lineEdit->text();
}

void CustomLineEditControl::setEnabled(bool enabled)
{
    m_lineEdit->setEnabled(enabled);
    m_toolButton->setEnabled(enabled);
}
