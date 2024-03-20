#include "stringattribute.h"
//#include "NodeManager.h"

StringAttribute::StringAttribute(AttributeType type, NodeBase *parentNode)
    :AttributeBase(type, parentNode)
{
    m_value = "";
}

StringAttribute::~StringAttribute()
{

}

// 设置/获取是否显示按钮
void StringAttribute::setShowButton(bool isShow)
{
    m_isShowButton = isShow;
}

bool StringAttribute::isShowButton()
{
    return m_isShowButton;
}

// 设置/获取按钮名字
void StringAttribute::setButtonString(const QString& buttonName)
{
    m_buttonString = buttonName;
}

QString StringAttribute::getButtonString()
{
    return m_buttonString;
}

// 设置按钮的功能
void StringAttribute::setButtonFunction(std::function<bool(QString&)> func)
{
    m_buttonFunc = func;
}

std::function<bool(QString&)> StringAttribute::getButtonFunction()
{
    return m_buttonFunc;
}
