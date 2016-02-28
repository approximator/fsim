/*!
 * @file main.cpp
 *
 * @brief Firces simulation entry point
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
