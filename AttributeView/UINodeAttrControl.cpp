#include "UINodeAttrControl.h"
#include "UIAttrTextControl.h"
#include "UIAttrFloatControl.h"
#include "UIAttrIntControl.h"
#include "UIAttrBoolControl.h"
#include "NodeBase.h"
#include "CustomCombineControl/UICustomGroupControl.h"
#include <QVBoxLayout>

UINodeAttrControl::UINodeAttrControl(QObject *parent)
    :QObject(parent)
{

}

UINodeAttrControl::~UINodeAttrControl()
{

}

QWidget *UINodeAttrControl::createNodeWidget(NodeBase *node)
{
    if (node == nullptr) {
        return nullptr;
    }

    // 获取所有的属性组
    const QList<AttributeGroup*> &attributeGroupList = node->getAllAttributeGroups();
    if (attributeGroupList.count() <= 0) {
        return nullptr;
    }

    QWidget *pWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(pWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(8);

    // 添加属性组
    foreach(auto group, attributeGroupList) {
        QWidget *groupControl = createAttributeGroupControl(group);
        mainLayout->addWidget(groupControl, 0, Qt::AlignTop);
    }
    mainLayout->addStretch();

    return pWidget;
}

QWidget *UINodeAttrControl::createAttributeControl(AttributeBase *attribute)
{
    if (attribute == nullptr) {
        return nullptr;
    }

    AttributeBase::AttributeType attrType = attribute->Type();
    switch (attrType) {
        case AttributeBase::LINEEDIT_TYPE: {
            return new UIAttrTextControl(attribute);
        }
        case AttributeBase::DOUBLESPINBOX_TYPE: {
            return new UIAttrFloatControl(attribute);
        }
        case AttributeBase::SPINBOX_TYPE: {
            return new UIAttrIntControl(attribute);
        }
        case AttributeBase::SWITCH_TYPE: {
            return new UIAttrBoolControl(attribute);
        }
        default:
            break;
    }

    return nullptr;
}

QWidget *UINodeAttrControl::createAttributeGroupControl(AttributeGroup *group)
{
    if (group == nullptr) {
            return nullptr;
    }

    // 添加group control
    UICustomGroupControl *groupControl = new UICustomGroupControl;
    groupControl->setTitleText(group->getDisplayName());

    // 添加属性控件
    const QList<AttributeBase*> &attributes = group->getAttributes();
    foreach(auto attribute, attributes) {
        QWidget *pWidget = createAttributeControl(attribute);
        if (pWidget == nullptr) {
            continue;
        }
        groupControl->addContentWidget(pWidget);
    }

    return groupControl;
}
