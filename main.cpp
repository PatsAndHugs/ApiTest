#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <apireader.h>
#include <triggerclass.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ApiReader>("com.example.api", 1, 0, "ApiReader");
    qmlRegisterType<TriggerClass>("com.example.api", 1, 0, "TriggerClass");
    //ApiReader apiReader;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ApiTest", "Main");
    //engine.rootContext()->setContextProperty(QStringLiteral("apiReader"), &apiReader);

    return app.exec();
}
