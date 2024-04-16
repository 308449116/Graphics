#include "customcombinecontrolbase.h"
//#include "CustomCore/customstyleconfig.h"

CustomCombineControlBase::CustomCombineControlBase(QWidget *parent)
    :CustomWidget(parent)
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_tagLabel = new QLabel();
    m_mainLayout->addWidget(m_tagLabel);
    m_tagLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_tagLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 设置默认第0列宽度
    setColumnWidth(0, 80);
//    g_StyleConfig->setCurrentStyle(this, "DefaultWidget");
}

CustomCombineControlBase::~CustomCombineControlBase()
{

}

void CustomCombineControlBase::setColumnWidth(int column, int width)
{
    int count = m_mainLayout->count();
    int number = 0;
    for (int i=0; i<count; ++i) {
        QWidget *pWidget = m_mainLayout->itemAt(i)->widget();
        if (pWidget == nullptr) {
            continue;
        }

        if (number == column) {
            pWidget->setFixedWidth(width);
            return;
        }
        number++;
    }
}

void CustomCombineControlBase::setColumnVisible(int column, bool visible)
{
    int count = m_mainLayout->count();
    int number = 0;
    for (int i=0; i<count; ++i) {
        QWidget *pWidget = m_mainLayout->itemAt(i)->widget();
        if (pWidget == nullptr) {
            continue;
        }

        if (number == column) {
            pWidget->setHidden(!visible);
            return;
        }
        number++;
    }
}

void CustomCombineControlBase::setColumnExpingVisible(int column, bool isExping)
{
    int count = m_mainLayout->count();
    int number = 0;
    for (int i=0; i<count; ++i)
    {
        QWidget *pWidget = m_mainLayout->itemAt(i)->widget();
        if (pWidget == nullptr) {
            continue;
        }

        if (number == column) {
            if (isExping){
                pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            } else {
                pWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            }
            return;
        }
        number++;
    }
}

void CustomCombineControlBase::setTagText(const QString& tagText)
{
    m_tagLabel->setText(tagText);
}

void CustomCombineControlBase::setTextAlign(Qt::Alignment alignment)
{
    m_tagLabel->setAlignment(alignment);
}

void CustomCombineControlBase::setWidth(int width)
{
    m_nWidth = width;
    this->setMinimumWidth(width);
}

void CustomCombineControlBase::setHeight(int height)
{
    m_nHeight = height;
    this->setMinimumHeight(height);
}

QSize CustomCombineControlBase::sizeHint() const
{
    QSize size(m_nWidth, m_nHeight);
    return size;
}
