#include "customcomboboxcontrol.h"

CustomComboBoxControl::CustomComboBoxControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_pCustomComboBox = new CustomComboBox;
    m_pCustomComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMainLayout->addWidget(m_pCustomComboBox);

    QObject::connect(m_pCustomComboBox, SIGNAL(currentIndexChanged(int)), \
                     this, SIGNAL(currentIndexChanged(int)));
    QObject::connect(m_pCustomComboBox, SIGNAL(currentIndexChanged(const QString &)), \
                     this, SIGNAL(currentTextChanged(const QString&)));
}

CustomComboBoxControl::~CustomComboBoxControl()
{

}

void CustomComboBoxControl::addItem(const QString& item)
{
    m_pCustomComboBox->addItem(item);
}

void CustomComboBoxControl::addItem(const QString& name, const QVariant& data)
{
    m_pCustomComboBox->addItem(name, data);
}

QString CustomComboBoxControl::getCurrentItem()
{
    return m_pCustomComboBox->currentText();
}

void CustomComboBoxControl::setCurrentItem(const QString& text)
{
    m_pCustomComboBox->setCurrentText(text);
}

void CustomComboBoxControl::setCurrentIndex(int index)
{
    m_pCustomComboBox->setCurrentIndex(index);
}

int CustomComboBoxControl::getCurrentIndex()
{
    return m_pCustomComboBox->currentIndex();
}

QVariant CustomComboBoxControl::getCurrentItemData()
{
    return m_pCustomComboBox->currentData();
}

int CustomComboBoxControl::getItemCount()
{
    return m_pCustomComboBox->count();
}

void CustomComboBoxControl::clearAllItems()
{
    m_pCustomComboBox->clear();
}
