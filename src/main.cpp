
#include "TSimWorld.h"

#include <QSettings>
#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    // Add path to search for Qt plugins
    QString pluginsPaths = QString("%1/%2").arg(
                QFileInfo(argv[0]).dir().path(),
                PLUGINS_PATH);
    QCoreApplication::addLibraryPath(pluginsPaths);

    QGuiApplication app(argc, argv);

    // Set up settings
    app.setOrganizationName("ForcesSimulator");
    app.setApplicationName("ForcesSimulator");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    QQmlApplicationEngine engine;

    QString qmlFilesPath = QString("%1/%2").arg(
                QCoreApplication::applicationDirPath(),
                QML_RELATIVE_PATH);
    engine.addImportPath(qmlFilesPath);
    qmlRegisterType<TSimWorld>("sim.world", 1, 0, "World");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
