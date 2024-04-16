#include "itemattributechangedcmd.h"
#include "attributemodel/attributebase.h"

ItemAttributeChangedCmd::ItemAttributeChangedCmd(AttributeBase *attribute,
                                                 const QVariant& value,
                                                 ViewGraphics *view,
                                                 bool isChanged)
    : m_attribute(attribute), m_value(value), m_view(view), m_isChanged(isChanged)

{
    QString nameString = QString("Changed Attribute %1 [%2] To [%3]")
                             .arg(attribute->getDisplayName())
                             .arg(attribute->getLastValue().toString())
                             .arg(attribute->getValue().toString());
    this->setText(nameString);
}

void ItemAttributeChangedCmd::undo()
{
    m_isChanged = true;
    m_attribute->setValue(m_attribute->getLastValue());
}

void ItemAttributeChangedCmd::redo()
{
    if (m_isChanged) {
        m_attribute->setValue(m_value);
    }
}
