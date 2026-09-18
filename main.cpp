#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

class Backend : public QObject
{
    Q_OBJECT

public slots:
    void startMigration()
    {
        qDebug() << "Migration started!";
    }
};

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.loadFromModule("V2p_gui", "App");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

#include "main.moc"