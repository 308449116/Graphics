#include "AttributeBase.h"
#include "BoolAttribute.h"
#include "RealAttribute.h"
#include "IntAttribute.h"
#include "StringAttribute.h"
#include "NodeBase.h"
#include "NodeManager.h"

AttributeBase::AttributeBase(AttributeType type, NodeBase *parentNode)
    :QObject (parentNode), m_type(type)
{
    QObject::connect(this, &AttributeBase::valueChanged, \
                     this, &AttributeBase::onValueChaned);
}

AttributeBase::~AttributeBase()
{

}

// 设置名字
void AttributeBase::setName(const QString& name)
{
    m_attributeName = name;
    if (m_displayName.isEmpty())
        m_displayName = name;
}

QString AttributeBase::getName() const
{
    return m_attributeName;
}

// 设置显示名字
void AttributeBase::setDisplayName(const QString& name)
{
    m_displayName = name;
}

QString AttributeBase::getDisplayName() const
{
    return m_displayName;
}

QString AttributeBase::getFullName() const
{
    if (m_pParentNode == nullptr)
        return "";

    return m_pParentNode->getNodeName() + "." + m_attributeName;
}

// 设置/获取父节点
void AttributeBase::setParentGroup(AttributeGroup *group)
{
    if (group == nullptr)
        return;

    this->setParent(group);
    m_pParentGroup = group;
}

AttributeGroup *AttributeBase::getParentGroup() const
{
    return m_pParentGroup;
}

// 设置/获取父节点
void AttributeBase::setParentNode(NodeBase *node)
{
    m_pParentNode = node;
}

NodeBase *AttributeBase::getParentNode() const
{
    return m_pParentNode;
}

// 设置/获取使能
void AttributeBase::setEnable(bool isEnabled)
{
    if (isEnabled != m_isEnabled) {
        m_isEnabled = isEnabled;
        emit enabledChanged(m_isEnabled);
    }
}

bool AttributeBase::isEnable() const
{
    return m_isEnabled;
}

AttributeBase *AttributeBase::createAttribute(const QString& name, AttributeType type, \
                                                  const QString& displayName)
{
    AttributeBase *attribute = nullptr;

    switch (type) {
        case SWITCH_TYPE: {
            attribute = new BoolAttribute(type);
            break;
        }
        case SPINBOX_TYPE:
        case COMBOBOX_TYPE: {
            attribute = new IntAttribute(type);
            break;
        }
        case DOUBLESPINBOX_TYPE: {
            attribute = new RealAttribute(type);
            break;
        }
        case LINEEDIT_TYPE: {
            attribute = new StringAttribute(type);
            break;
        }
        default:
            break;
    }

    if (attribute == nullptr)
        return nullptr;

    // 设置属性名称
    attribute->setDisplayName(displayName);
    attribute->setName(name);
    return attribute;
}

AttributeBase::AttributeType AttributeBase::Type() const
{
    return m_type;
}

QVariant AttributeBase::getLastValue() const
{
    return m_lastValue;
}

QString AttributeBase::getTypeName() const
{
    AttributeType type = this->Type();
    switch (type) {
        case SWITCH_TYPE:
            return "Switch";
        case SPINBOX_TYPE:
            return "SpinBox";
        case DOUBLESPINBOX_TYPE:
            return "DoubleSpinBox";
        case LINEEDIT_TYPE:
            return "LineEdit";
        case COMBOBOX_TYPE:
            return "ComboBox";
    }

    return "";
}

// 设置/获取属性值
void AttributeBase::setValue(const QVariant& value, bool cmd)
{
    // 处理第一次
    if (m_isFirstSetValue) {
        m_lastValue = value;
        m_isFirstSetValue = false;
    }

    // 判断是否需要发送信号
    bool needSendSignal = true;
    if (m_value == value)
        needSendSignal = false;

    QVariant tempValue = m_value;
    m_value = value;

    if (needSendSignal) {
        m_lastValue = tempValue;
        emit valueChanged(value, cmd);
    }
}

QVariant AttributeBase::getValue() const
{
    return m_value;
}

void AttributeBase::onValueChaned(const QVariant& value, bool cmd)
{
    g_nodeManager->informAttributeValueChanged(this, value, cmd);
}
