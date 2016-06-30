import qbs
import qbs.FileInfo
import qbs.ModUtils

Project {
    name: "contrib_projects"

    references: [
        "Qt-QML-Models/QtQmlModels.qbs",
        "Qt-Super-Macros/QtSuperMacros.qbs"
    ]

}
