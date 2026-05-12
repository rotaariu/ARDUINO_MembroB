#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "musicprovider.h"

using namespace Qt::StringLiterals;  // ← aggiungi questo

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MusicProvider provider;

    engine.rootContext()->setContextProperty("musicProvider", &provider);

    const QUrl url(u"qrc:/qt/qml/Interfaccia/Main.qml"_s);  // ← non più qrc:/Interfaccia/

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}