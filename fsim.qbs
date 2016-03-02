import qbs
import qbs.FileInfo

Project {
    name: "ForcesSimlation"

    qbsSearchPaths: "modules/Qt-Qbs-Application/qbs"

    property path fsimDataPath: "data"
    property path fsimQmlInstallDir: FileInfo.joinPaths(fsimDataPath, "qml")
    property path fsimPluginsInstallDir: FileInfo.joinPaths(fsimDataPath, "plugins")

    property bool justRunExperiments: false

    references: [
        "src/ForcesSimulationApp.qbs",
        "modules/Qt-QML-Models/QtQmlModels.qbs",
        "modules/Qt-Super-Macros/QtSuperMacros.qbs",
    ]
}
