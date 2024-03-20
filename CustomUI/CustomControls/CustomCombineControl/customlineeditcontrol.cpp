#include "customlineeditcontrol.h"

CustomLineEditControl::CustomLineEditControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_pLineEdit = new CustomLineEdit;
    m_pMainLayout->addWidget(m_pLineEdit);
    m_pLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pToolButton = new QToolButton;
    m_pMainLayout->addWidget(m_pToolButton);

    // 转发信后
    QObject::connect(m_pLineEdit, &QLineEdit::textChanged, this, &CustomLineEditControl::textChanged);
    QObject::connect(m_pLineEdit, &QLineEdit::editingFinished, this, &CustomLineEditControl::editingFinished);
    QObject::connect(m_pToolButton, &QToolButton::clicked, this, &CustomLineEditControl::clickedToolButton);

    this->setWidth(400);
    this->setHeight(30);
}

CustomLineEditControl::~CustomLineEditControl()
{

}

// 设置按钮相关
void CustomLineEditControl::setToolButtonVisible(bool isVisible)
{
    m_pToolButton->setVisible(isVisible);
}

void CustomLineEditControl::setToolButtonText(const QString& text)
{
    m_pToolButton->setText(text);
}

void CustomLineEditControl::setToolButtonIcon(const QIcon& icon)
{
    m_pToolButton->setIcon(icon);
}

// 设置文本
void CustomLineEditControl::setText(const QString& string)
{
    m_pLineEdit->setText(string);
}

QString CustomLineEditControl::getText()
{
    return m_pLineEdit->text();
}
