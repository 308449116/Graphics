#include "NodeManager.h"

NodeManager::NodeManager(QObject* parent)
    :QObject(parent)
{

}

NodeManager::~NodeManager()
{

}

NodeManager* NodeManager::getInstance()
{
    static NodeManager instance;
    return &instance;
}

void NodeManager::informAttributeValueChanged(AttributeBase* pAttribute, const QVariant& value, bool cmd)
{
    emit signalAttrValueChanged(pAttribute, value, cmd);
}
