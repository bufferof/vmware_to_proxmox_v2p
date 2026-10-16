#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Backend.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Backend backend;

    engine.rootContext()->setContextProperty(
        "backend", &backend
    );

    engine.loadFromModule("V2p_gui", "App");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}