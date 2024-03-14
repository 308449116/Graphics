#ifndef UIATTRTEXTCONTROL_H
#define UIATTRTEXTCONTROL_H

#include "CustomCombineControl/UICustomLineEditControl.h"
#include "StringAttribute.h"
#include <QString>

class UIAttrTextControl : public UICustomLineEditControl
{
    Q_OBJECT

public:
    UIAttrTextControl(AttributeBase* attribute = nullptr, QWidget* parent = nullptr);
    ~UIAttrTextControl();

    // 设置属性
    void setAttribute(AttributeBase* attribute);

private:
    StringAttribute* m_attribute = nullptr;
    QString m_tempString;

private slots:
    void onTextAttrValueChanged(const QVariant& value);
    void onControlTextChanged(const QString& value);
    void onControlEditFinished();

    void onClickedToolButton();
};

#endif
