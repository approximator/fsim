import qbs

QmlModule {
    name: "qml_material"
    srcPrefix: "qml-material/modules"
    targetDirectory: FileInfo.joinPaths(
                         project.fsimInstallRoot,
                         project.fsimInstallDir,
                         project.fsimQmlInstallDir
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
