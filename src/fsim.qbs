import qbs
import qbs.FileInfo

Product {
    type: "application" // no Mac app bundle

    property path fsimDataPath: "data"
    property path fsimQmlInstallDir: FileInfo.joinPaths(fsimDataPath, "qml")
    property path fsimPluginsInstallDir: FileInfo.joinPaths(fsimDataPath, "plugins")

    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++11"
    cpp.warningLevel: "all"
    cpp.treatWarningsAsErrors: false

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

    cpp.defines: [
        'FSIM_QML_MODULES_PATH="' + FileInfo.relativePath("", fsimQmlInstallDir) + '"',
        'FSIM_PLUGINS_PATH="' + FileInfo.relativePath("", fsimPluginsInstallDir) + '"',
    ]

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

    //    references: [
    //        fgapSourceRoot + "contrib/submodules.qbs",
    //        "FlightController/FlightController.qbs",
    //        "Gui/qml/qml.qbs"
    //    ]

}
