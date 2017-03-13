#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Model* pluginModel READ getPluginModel CONSTANT)
    Q_PROPERTY(Model* instanceModel READ getInstanceModel CONSTANT)

public:
    explicit Controller(QObject *parent = 0);

    Model* getPluginModel() { return m_pluginModel; }
    Model* getInstanceModel() { return m_instanceModel; }

    QJsonObject dispatch(QString func, QVariantList args=QVariantList());

private:
    Model* m_pluginModel;
    Model* m_instanceModel;
};

#endif // CONTROLLER_H
