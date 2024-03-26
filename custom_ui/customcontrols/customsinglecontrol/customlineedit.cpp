#include "customlineedit.h"
#include <QKeyEvent>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPainter>
//#include "CustomCore/customstyleconfig.h"

CustomLineEdit::CustomLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    m_pButton = new CustomCloseButton;
    m_pButton->setFixedSize(12, 12);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(m_pButton, 0, Qt::AlignRight | Qt::AlignVCenter);

    setCloseButtonEnable(false);

    // 关联信号和槽
    QObject::connect(this, &CustomLineEdit::textChanged, this, &CustomLineEdit::onTextChanged);
    QObject::connect(m_pButton, &CustomCloseButton::clicked, this, &CustomLineEdit::onCloseButtonClicked);
}

CustomLineEdit::~CustomLineEdit()
{

}

//void CustomLineEdit::keyPressEvent(QKeyEvent *event)
//{
//    QLineEdit::keyPressEvent(event);
//    event->accept();
//}

void CustomLineEdit::setCloseButtonEnable(bool isEnabled)
{
    m_isToolButtonEnable = isEnabled;
    if (!isEnabled)
        m_pButton->setVisible(false);
}

void CustomLineEdit::onTextChanged(const QString& textChanged)
{
    if (!m_isToolButtonEnable)
    {
        emit currentTextChanged(textChanged);
        return;
    }

    if (textChanged.isEmpty())
        m_pButton->setVisible(false);
    else
        m_pButton->setVisible(true);
    emit currentTextChanged(textChanged);
}

void CustomLineEdit::onCloseButtonClicked()
{
    this->setText("");
}
// ==============================================================
CustomCloseButton::CustomCloseButton(QWidget *parent)
    :CustomWidget(parent)
{
    this->setMouseTracking(true);
//    g_StyleConfig->setCurrentStyle(this, "TransparentBgWidget");
}

CustomCloseButton::~CustomCloseButton()
{

}

void CustomCloseButton::customPaint(QPainter *painter)
{
    QColor penColor(200, 80, 80);
    if (m_isHoveredOn)
        penColor = QColor(200, 200, 200);

    // 设置画笔
    QPen pen;
    pen.setWidth(2);
    pen.setColor(penColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    // 绘制关闭
    QRect rect = this->rect();
    rect.adjust(2, 2, -2, -2);
    painter->drawLine(rect.topLeft(), rect.bottomRight());
    painter->drawLine(rect.topRight(), rect.bottomLeft());
}

void CustomCloseButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    CustomWidget::mousePressEvent(event);
}

void CustomCloseButton::enterEvent(QEnterEvent *event)
{
    m_isHoveredOn = true;
    this->setCursor(Qt::PointingHandCursor);
    this->update();
    CustomWidget::enterEvent(event);
}

void CustomCloseButton::leaveEvent(QEvent *event)
{
    m_isHoveredOn = false;
    this->setCursor(Qt::ArrowCursor);
    this->update();
    CustomWidget::leaveEvent(event);
}
