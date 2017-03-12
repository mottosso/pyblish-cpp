#include <QtQml>
#include <QtCore>
#include <QtGui>

#include "controller.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Controller controller;

    engine.rootContext()->setContextProperty("controller", &controller);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
