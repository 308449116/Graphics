#include "customcomboboxcontrol.h"

CustomComboBoxControl::CustomComboBoxControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_customComboBox = new CustomComboBox;
    m_customComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_mainLayout->addWidget(m_customComboBox);

    QObject::connect(m_customComboBox, SIGNAL(currentIndexChanged(int)), \
                     this, SIGNAL(currentIndexChanged(int)));
    QObject::connect(m_customComboBox, SIGNAL(currentIndexChanged(const QString &)), \
                     this, SIGNAL(currentTextChanged(const QString&)));
}

CustomComboBoxControl::~CustomComboBoxControl()
{

}

void CustomComboBoxControl::addItem(const QString& item)
{
    m_customComboBox->addItem(item);
}

void CustomComboBoxControl::addItem(const QString& name, const QVariant& data)
{
    m_customComboBox->addItem(name, data);
}

QString CustomComboBoxControl::getCurrentItem()
{
    return m_customComboBox->currentText();
}

void CustomComboBoxControl::setCurrentItem(const QString& text)
{
    m_customComboBox->setCurrentText(text);
}

void CustomComboBoxControl::setCurrentIndex(int index)
{
    m_customComboBox->setCurrentIndex(index);
}

int CustomComboBoxControl::getCurrentIndex()
{
    return m_customComboBox->currentIndex();
}

QVariant CustomComboBoxControl::getCurrentItemData()
{
    return m_customComboBox->currentData();
}

int CustomComboBoxControl::getItemCount()
{
    return m_customComboBox->count();
}

void CustomComboBoxControl::clearAllItems()
{
    m_customComboBox->clear();
}

void CustomComboBoxControl::setEnabled(bool enabled)
{
    m_customComboBox->setEnabled(enabled);
}
