import qbs
import qbs.FileInfo

Project {
    name: "ForcesSimlation"

    qbsSearchPaths: "modules/Qt-Qbs-Application/qbs"

    property path fsimAppTarget: "ForcesSimlation"
    property path fsimInstallRoot: qbs.installRoot
    property path fsimInstallDir: qbs.targetOS.contains("osx")
                                   ? fsimAppTarget + ".app/Contents"
                                   : fsimAppTarget
    property path fsimDataPath: qbs.targetOS.contains("osx")
                                ? "Resources"
                                : "data"
    property path fsimBinDir: qbs.targetOS.contains("osx")
                                  ? "MacOS"
                                  : ""
    property path fsimQmlInstallDir: FileInfo.joinPaths(fsimDataPath, "qml")
    property path fsimPluginsInstallDir: FileInfo.joinPaths(fsimDataPath, "plugins")

    property bool justRunExperiments: false

    references: [
        "src/ForcesSimulationApp.qbs",
        "modules/qml-material-deploy.qbs",
        "modules/Qt-QML-Models/QtQmlModels.qbs",
        "modules/Qt-Super-Macros/QtSuperMacros.qbs",
    ]
}
