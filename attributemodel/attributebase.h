#ifndef ATTRIBUTEBASE_H
#define ATTRIBUTEBASE_H

#include <QObject>
#include <QVariant>

class NodeBase;
class AttributeGroup;
class AttributeBase : public QObject
{
    Q_OBJECT

public:
    enum AttributeType {
        SWITCH_TYPE,             // Switch类型
        SPINBOX_TYPE,            // SpinBox类型
        DOUBLESPINBOX_TYPE,      // doubleSpinBox类型
        LINEEDIT_TYPE,           // LineEdit类型
        COMBOBOX_TYPE            // ComboBox类型
    };

public:
    AttributeBase(AttributeType type, NodeBase *parentNode = nullptr);
    virtual ~AttributeBase();

    static AttributeBase *createAttribute(const QString& name, AttributeType type, const QString& displayName = "");

    AttributeType Type() const;

    // 获取上一次的属性值
    QVariant getLastValue() const;

    // 类型名转字符串
    QString getTypeName() const;

    // 设置/获取属性值
    virtual void setValue(const QVariant& value, bool cmd = false);
    virtual QVariant getValue() const;

    // 设置/获取名字
    void setName(const QString& name);
    QString getName() const;

    // 设置/获取显示名字
    void setDisplayName(const QString& name);
    QString getDisplayName() const;

    // 获取全名
    QString getFullName() const;

    // 设置/获取父节点组
    void setParentGroup(AttributeGroup *group);
    AttributeGroup *getParentGroup() const;

    // 设置/获取父节点
    void setParentNode(NodeBase *node);
    NodeBase *getParentNode() const;

    // 设置/获取使能
    void setEnabled(bool isEnabled);
    bool isEnable() const;

signals:
    void enabledChanged(bool enabled);
    void valueChanged(const QVariant& value, bool cmd = false);

private slots:
    void onValueChaned(const QVariant& value, bool cmd);

protected:
    QString m_displayName;
    QString m_attributeName;

    QVariant m_value;
    QVariant m_lastValue;
    bool m_isEnabled = true;
    bool m_isFirstSetValue = true;

    AttributeType m_type;
    NodeBase *m_parentNode = nullptr;
    AttributeGroup *m_parentGroup = nullptr;
};

#endif
