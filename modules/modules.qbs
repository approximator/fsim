import qbs
import qbs.FileInfo
import qbs.ModUtils

Project {
    name: "contrib_projects"

    QmlModule {
        name: "qml_material"
        srcPrefix: "qml-material/modules"

        targetDirectory: FileInfo.joinPaths(
                             project.appInstallRoot,
                             project.appInstallDir,
                             project.appQmlInstallDir
                             )

        files: [
            "qml-material/modules/Material/*",
            "qml-material/modules/Material/Extras",
            "qml-material/modules/Material/fonts",
            "qml-material/modules/Material/icons",
            "qml-material/modules/Material/ListItems/*",
            "qml-material/modules/QtQuick/"
        ]

    }

    references: [
        "Qt-QML-Models/QtQmlModels.qbs",
        "Qt-Super-Macros/QtSuperMacros.qbs"
    ]

}
