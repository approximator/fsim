/*!
 * @file main.cpp
 *
 * @brief Firces simulation entry point
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 20, 2016
 */

#include "TSimWorld.h"
#include "experiment_runner.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QtQml>

int main(int argc, char *argv[])
{
    // Add path to search for Qt plugins
    QString pluginsPaths = QString("%1/%2").arg(QFileInfo(argv[0]).dir().path(), FSIM_PLUGINS_PATH);
    QCoreApplication::addLibraryPath(pluginsPaths);

    QGuiApplication app(argc, argv);
    qDebug() << "Looking for plugins in " << app.libraryPaths();

    // Set up settings
    app.setOrganizationName("ForcesSimulator");
    app.setApplicationName("ForcesSimulator");
    QSettings::setDefaultFormat(QSettings::IniFormat);

#ifdef JUST_RUN_EXPERIMENTS
    qDebug() << "Do not start UI. Running experiments only";
    return ExperimentRunner().run();
#endif

    QQmlApplicationEngine engine;

    QString qmlFilesPath = QString("%1/%2").arg(QCoreApplication::applicationDirPath(), FSIM_QML_MODULES_PATH);
    engine.addImportPath(qmlFilesPath);
    qmlRegisterType<TSimWorld>("sim.world", 1, 0, "World");
    qRegisterMetaType<TPointsModel *>("TPointsModel*");
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
