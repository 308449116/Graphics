#ifndef UICUSTOMFONTCOMBOBOXCONTROL_H
#define UICUSTOMFONTCOMBOBOXCONTROL_H

#include "UICustomCombineControlBase.h"
#include <QWidget>

class QFontComboBox;
class UICustomFontComboBoxControl : public UICustomCombineControlBase
{
    Q_OBJECT

public:
    UICustomFontComboBoxControl(QWidget *parent = nullptr);
    ~UICustomFontComboBoxControl();

private:
    QFontComboBox *m_pComboBox = nullptr;
};

#endif
