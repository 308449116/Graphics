#ifndef UICUSTOMTEXTEDITTAGCONTROL_H
#define UICUSTOMTEXTEDITTAGCONTROL_H

#include "UICustomSingleControl/UICustomTextEdit.h"
#include "UICustomCombineControlBase.h"

#include <QWidget>

class UICustomTextEditTagControl : public UICustomCombineControlBase
{
    Q_OBJECT
public:
    UICustomTextEditTagControl(QWidget* parent = nullptr);
    ~UICustomTextEditTagControl();

    // 获取当前文本
    QString getCurrentText();
    void setCurrentText(const QString& text);

private:
    UICustomTextEdit* m_pTextEdit = nullptr;
};

#endif
