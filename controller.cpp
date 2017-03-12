#include <vector>
#include <iostream>

#include <QtWidgets>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>

#include "controller.h"
#include "model.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
	m_pluginModel = new Model(this);
    m_instanceModel = new Model(this);

    // blocking..
    QJsonObject pluginsResponse = dispatch("discover");
    QJsonArray pluginsArray = pluginsResponse["payload"].toArray();

    for (auto pluginRef : pluginsArray)
    {
        QJsonObject pluginObject = pluginRef.toObject();

        Plugin plugin {
            pluginObject["name"].toString(),
            pluginObject["family"].toString()
        };

        m_pluginModel->addPlugin(plugin);
    }

    // Perform collection
    for (auto pluginRef : pluginsArray)
    {
        QJsonObject pluginObject = pluginRef.toObject();

        bool isCollector = pluginObject["type"].toString() == "Collector";
        bool isContextPlugin = !pluginObject["instanceEnabled"].toBool();

        if (isCollector && isContextPlugin)
        {
            std::cout << "processing " << pluginObject["name"].toString().toUtf8().constData() << std::endl;
            dispatch("process", {pluginObject});
        }
    }

    // Populate instances
    QJsonObject contextResponse = dispatch("context");
    QJsonObject contextObject = contextResponse["payload"].toObject();
    QJsonArray instancesArray = contextObject["children"].toArray();

    for (auto instanceRef : instancesArray)
    {
        QJsonObject instanceObject = instanceRef.toObject();
        std::cout << "Adding " << instanceObject["name"].toString().toUtf8().constData() << std::endl;

        Plugin instance {
            instanceObject["name"].toString(),
            "default"
        };

        m_instanceModel->addPlugin(instance);
    }

//    m_pluginModel->addPlugin(Plugin("Wolf", "Medium"));
//    m_pluginModel->addPlugin(Plugin("Polar bear", "Large"));
//    m_pluginModel->addPlugin(Plugin("Quoll", "Small"));
}

Model* Controller::getPluginModel()
{
    return m_pluginModel;
}

Model* Controller::getInstanceModel()
{
    return m_instanceModel;
}

QJsonObject Controller::dispatch(QString func, QVariantList args)
{
    QVariantMap payload;
    payload.insert("name", func);
    payload.insert("args", args);

    QVariantMap request;
    request.insert("header", "pyblish-qml:popen.request-1.0");
    request.insert("payload", payload);

    QJsonObject object = QJsonObject::fromVariantMap(request);

    QJsonDocument document;
    document.setObject(object);

    // Send to Python..
    std::cout << document.toJson(QJsonDocument::Compact).constData() << std::endl;

    // Read from Python..
    std::string response;
    std::getline(std::cin, response);

    QJsonDocument result = QJsonDocument::fromJson(response.c_str());

    if (result.isNull())
    {
        std::cerr << "Invalid JSON" << std::endl;
    }

    return result.object();
}
