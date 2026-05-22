#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "serialcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("LED Matrix Controller");
    app.setOrganizationName("ArduinoProject");

    // Registra SerialController come tipo QML utilizzabile
    qmlRegisterType<SerialController>("com.arduino", 1, 0, "SerialController");

    QQmlApplicationEngine engine;

    // Crea istanza globale accessibile da QML come "serialCtrl"
    SerialController serialController;
    engine.rootContext()->setContextProperty("serialCtrl", &serialController);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
