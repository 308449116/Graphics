#include "nodeattrcontrol.h"
#include "attrtextcontrol.h"
#include "attrfloatcontrol.h"
#include "attrintcontrol.h"
#include "attrboolcontrol.h"
#include "nodebase.h"
#include "CustomCombineControl/customgroupcontrol.h"
#include <QVBoxLayout>

NodeAttrControl::NodeAttrControl(QObject *parent)
    :QObject(parent)
{

}

NodeAttrControl::~NodeAttrControl()
{

}

QWidget *NodeAttrControl::createNodeWidget(NodeBase *node)
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

QWidget *NodeAttrControl::createAttributeControl(AttributeBase *attribute)
{
    if (attribute == nullptr) {
        return nullptr;
    }

    AttributeBase::AttributeType attrType = attribute->Type();
    switch (attrType) {
        case AttributeBase::LINEEDIT_TYPE: {
            return new AttrTextControl(attribute);
        }
        case AttributeBase::DOUBLESPINBOX_TYPE: {
            return new AttrFloatControl(attribute);
        }
        case AttributeBase::SPINBOX_TYPE: {
            return new AttrIntControl(attribute);
        }
        case AttributeBase::SWITCH_TYPE: {
            return new AttrBoolControl(attribute);
        }
        default:
            break;
    }

    return nullptr;
}

QWidget *NodeAttrControl::createAttributeGroupControl(AttributeGroup *group)
{
    if (group == nullptr) {
            return nullptr;
    }

    // 添加group control
    CustomGroupControl *groupControl = new CustomGroupControl;
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
