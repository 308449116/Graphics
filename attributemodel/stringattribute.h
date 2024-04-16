#ifndef STRINGATTRIBUTE_H
#define STRINGATTRIBUTE_H

#include "attributebase.h"
#include <functional>

class StringAttribute : public AttributeBase
{
    Q_OBJECT

public:
    StringAttribute(AttributeType type, NodeBase *parentNode = nullptr);
    ~StringAttribute();

    // 设置/获取是否显示按钮
    void setShowButton(bool isShow);
    bool isShowButton();

    // 设置/获取按钮名字
    void setButtonString(const QString& buttonName);
    QString getButtonString();

    // 设置按钮的功能
    void setButtonFunction(std::function<bool(QString&)> func);
    std::function<bool(QString&)> getButtonFunction();

private:
    bool m_isShowButton = false;
    QString m_buttonString = "";
    std::function<bool(QString&)> m_buttonFunc;
};

#endif
