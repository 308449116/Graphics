#ifndef CUSTOMCOMBOBOXCONTROL_H
#define CUSTOMCOMBOBOXCONTROL_H

#include "customcombinecontrolbase.h"
#include "custom_ui/customcontrols/customsinglecontrol/customcombobox.h"

class CustomComboBoxControl : public CustomCombineControlBase
{
    Q_OBJECT

public:
    CustomComboBoxControl(QWidget *parent = nullptr);
    ~CustomComboBoxControl();

    // 添加元素
    void addItem(const QString& item);
    void addItem(const QString& name, const QVariant& data);

    // 获取当前元素
    void setCurrentItem(const QString& text);
    QString getCurrentItem();
    void setCurrentIndex(int index);
    int getCurrentIndex();

    // 获取当前数据
    QVariant getCurrentItemData();

    // 获取当前个数
    int getItemCount();

    // 清除所有元素
    void clearAllItems();

    //设置控件是否使能
    void setEnabled(bool enabled);

signals:
    void currentTextChanged(const QString& str);
    void currentIndexChanged(int index);

private:
    CustomComboBox *m_customComboBox = nullptr;
};

#endif
