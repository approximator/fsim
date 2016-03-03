import qbs
import qbs.FileInfo

CppApplicationBase {
    targetName: project.fsimAppTarget

    property stringList commonDefines: [
        'FSIM_QML_MODULES_PATH="' + FileInfo.relativePath(project.fsimBinDir, fsimQmlInstallDir) + '"',
        'FSIM_PLUGINS_PATH="' + FileInfo.relativePath(project.fsimBinDir, fsimPluginsInstallDir) + '"',
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
        qbs.installPrefix: project.fsimInstallDir
        qbs.install: true
        qbs.installDir: project.fsimBinDir
    }

    Properties {
        condition: project.justRunExperiments
        cpp.defines: commonDefines.concat(['JUST_RUN_EXPERIMENTS'])
    }
}
