import qbs
import qbs.FileInfo

import "../modules/Qt-Qbs-Application/qbs/imports/CppApplicationBase.qbs" as CppApplicationBase

Project {
    name: "ForcesSimlation"

    property path fsimDataPath: "data"
    property path fsimQmlInstallDir: FileInfo.joinPaths(fsimDataPath, "qml")
    property path fsimPluginsInstallDir: FileInfo.joinPaths(fsimDataPath, "plugins")

    property bool justRunExperiments: false 

    CppApplicationBase {

        property stringList commonDefines: [
            'FSIM_QML_MODULES_PATH="' + FileInfo.relativePath("", fsimQmlInstallDir) + '"',
            'FSIM_PLUGINS_PATH="' + FileInfo.relativePath("", fsimPluginsInstallDir) + '"',
        ]

        property stringList additionalDefines: []

        Depends { name: "Qt"; submodules: ["qml", "quick", "gui", "svg"] }
        Depends { name: "libqtqmltricks-qtqmlmodels" }
        Depends { name: "libqtqmltricks-qtsupermacros" }

        Group {
            name: "Sources"
            files: [
                "*.cpp",
                "*.h"
            ]
        }

        Group {
            name: "resources"
            files: "*.qrc"
        }

        cpp.defines: commonDefines

        Group {
            fileTagsFilter: "application"
            qbs.install: true
        }

        Group {
            name: "QmlMaterial"
            prefix: "../modules/qml-material/modules/"
            files: [
                "Material",
                "QtQuick",
            ]
            qbs.install: true
            qbs.installDir: fsimQmlInstallDir
        }

        Properties {
            condition: project.justRunExperiments
            cpp.defines: commonDefines.concat(['JUST_RUN_EXPERIMENTS'])
        }
    }

    references: [
        "../modules/Qt-QML-Models/QtQmlModels.qbs",
        "../modules/Qt-Super-Macros/QtSuperMacros.qbs",
    ]
}
