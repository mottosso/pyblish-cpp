#include <QtCore>
#include <QtGui>
#include <QtQml>
#include <iostream>

#include "controller.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont openSans(family);
    openSans.setPointSize(8);
    app.setFont(openSans);

    QQmlApplicationEngine engine;

    // Quit on failed load of QML
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, [](QObject *object) {
        if (object == NULL)
            exit(1);
    });

    QStringList args = app.arguments();
    if (args.size() > 1 && args.at(1) == "--aschild")
    {
        std::cout << "Running as child.." << std::endl;
        Controller* controller = new Controller();
        engine.rootContext()->setContextProperty("controller", controller);
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
