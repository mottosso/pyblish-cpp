#include <string>
#include <vector>
#include <iostream>

#include <QtWidgets>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>

#include "window.h"


QJsonObject dispatch(QString func, QVariantList args=QVariantList())
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


Window::Window(QWidget *parent) : QWidget(parent)
{
    QListWidget *instanceView = new QListWidget();
    QListWidget *pluginView = new QListWidget();

    QWidget *spacerTab = new QWidget();
    QPushButton *overviewTab = new QPushButton("Overview");
    QPushButton *terminalTab = new QPushButton("Terminal");

    QWidget *header = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->addWidget(overviewTab);
    headerLayout->addWidget(terminalTab);
    headerLayout->addWidget(spacerTab, 1);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *body = new QWidget();
    QHBoxLayout *bodyLayout = new QHBoxLayout(body);
    bodyLayout->addWidget(instanceView);
    bodyLayout->addWidget(pluginView);

    QWidget *spacer = new QWidget();
    QPushButton *publishButton = new QPushButton(">");

    QWidget *footer = new QWidget();
    QHBoxLayout *footerLayout = new QHBoxLayout(footer);
    footerLayout->addWidget(spacer, 1);
    footerLayout->addWidget(publishButton);
    footerLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(header);
    layout->addWidget(body);
    layout->addWidget(footer);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // blocking..
    QJsonObject pluginsResponse = dispatch("discover");
    QJsonArray pluginsArray = pluginsResponse["payload"].toArray();

    for (auto pluginRef : pluginsArray)
    {
        QJsonObject pluginObject = pluginRef.toObject();
        QListWidgetItem *item = new QListWidgetItem(pluginObject["name"].toString());
        pluginView->addItem(item);
    }

    // Perform collection
    for (auto pluginRef : pluginsArray)
    {
        QJsonObject pluginObject = pluginRef.toObject();
        if (pluginObject["type"].toString() == "Collector" &&
            !pluginObject["instanceEnabled"].toBool())
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
        QListWidgetItem *item = new QListWidgetItem(instanceObject["name"].toString());
        instanceView->addItem(item);
    }

    QObject::connect(pluginView, &QListWidget::currentItemChanged,
                     this, &Window::onItemChanged);

    resize(500, 600);
    setWindowTitle("My Window");
}

void Window::onItemChanged(QListWidgetItem* item)
{
    std::cout << "Changed to " << item->data(Qt::DisplayRole).toString().toUtf8().constData() << std::endl;
}
