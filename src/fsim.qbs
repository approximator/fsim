import qbs
import qbs.FileInfo

Project {
    name: "ForcesSimlation"

    property path fsimDataPath: "data"
    property path fsimQmlInstallDir: FileInfo.joinPaths(fsimDataPath, "qml")
    property path fsimPluginsInstallDir: FileInfo.joinPaths(fsimDataPath, "plugins")

    property bool justRunExperiments: false

    Product {
        type: "application" // no Mac app bundle

        Depends { name: "libqtqmltricks-qtqmlmodels" }
        Depends { name: "libqtqmltricks-qtsupermacros" }

        Depends { name: "cpp" }
        cpp.cxxLanguageVersion: "c++11"
        cpp.warningLevel: "all"

        property stringList commonDefines: [
            'FSIM_QML_MODULES_PATH="' + FileInfo.relativePath("", fsimQmlInstallDir) + '"',
            'FSIM_PLUGINS_PATH="' + FileInfo.relativePath("", fsimPluginsInstallDir) + '"',

        ]

        Properties {
            condition: qbs.targetOS.contains("linux")
            cpp.commonCompilerFlags: ['-Wall', '-Wextra', '-pedantic', '-Weffc++', '-Wold-style-cast']
            cpp.systemIncludePaths: [
                FileInfo.joinPaths(qbs.getEnv('QTDIR'), 'include'),
                FileInfo.joinPaths(qbs.getEnv('QTDIR'), 'include/QtCore'),
                FileInfo.joinPaths(qbs.getEnv('QTDIR'), 'include/QtGui'),
                FileInfo.joinPaths(qbs.getEnv('QTDIR'), 'include/QtQml'),
            ]
        }

        cpp.rpaths: qbs.targetOS.contains("osx")
                    ? ["@executable_path/../lib"]
                    : ["$ORIGIN/../lib"]

        Properties {
            //OS X special compiler configs
            condition: qbs.targetOS.contains("osx")
            cpp.cxxStandardLibrary: "libc++"
        }

        Depends { name: "Qt"; submodules: ["qml", "quick", "gui", "svg"] }

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
