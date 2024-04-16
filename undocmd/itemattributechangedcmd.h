#ifndef ITEMATTRIBUTECHANGEDCMD_H
#define ITEMATTRIBUTECHANGEDCMD_H

#include <QVariant>
#include <QPointer>
#include <QUndoCommand>

class ViewGraphics;
class AttributeBase;

class ItemAttributeChangedCmd : public QUndoCommand
{
public:
    ItemAttributeChangedCmd(AttributeBase *attribute,
                            const QVariant& value,
                            ViewGraphics *view,
                            bool isChanged);

    virtual void undo() override;
    virtual void redo() override;

private:
    QPointer<AttributeBase> m_attribute;
    QVariant m_value;
    ViewGraphics *m_view = nullptr;
    bool m_isChanged = true;
};

#endif // ITEMATTRIBUTECHANGEDCMD_H
