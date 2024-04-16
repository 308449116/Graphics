#ifndef ATTRTEXTCONTROL_H
#define ATTRTEXTCONTROL_H

#include "custom_ui/customcontrols/customcombinecontrol/customlineeditcontrol.h"
#include "attributemodel/stringattribute.h"
#include <QString>

class AttrTextControl : public CustomLineEditControl
{
    Q_OBJECT

public:
    AttrTextControl(AttributeBase *attribute = nullptr, QWidget *parent = nullptr);
    ~AttrTextControl();

    // 设置属性
    void setAttribute(AttributeBase *attribute);

private slots:
    void onTextAttrValueChanged(const QVariant& value);
//    void onControlTextChanged(const QString& value);
    void onControlEditFinished();

    void onClickedToolButton();

private:
    StringAttribute *m_attribute = nullptr;
    //    QString m_tempString;
};

#endif
