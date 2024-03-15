#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QObject>

#define g_nodeManager NodeManager::getInstance()

class AttributeBase;
class NodeManager : public QObject
{
    Q_OBJECT

public:
    NodeManager(QObject *parent = nullptr)  ;
    ~NodeManager();

    static NodeManager *getInstance();

    // 信号通知
    void informAttributeValueChanged(AttributeBase *pAttribute, const QVariant& value, bool cmd = false);

signals:
    void signalAttrValueChanged(AttributeBase *pAttribute, const QVariant& value, bool cmd = false);
};

#endif
