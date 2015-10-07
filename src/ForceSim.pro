TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    TPoint.cpp \
    TScreen.cpp \
    TSimWorld.cpp

HEADERS += \
    TPoint.h \
    TScreen.h \
    TSimWorld.h

RESOURCES += qml.qrc

BUILD_TYPE = Release
CONFIG(debug, debug|release) {
    BUILD_TYPE = Debug
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

isEmpty(BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    BUILD_TREE = $$clean_path($$OUT_PWD)
    BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
    BUILD_TREE = $$system_path($$BUILD_TREE)
}

ROOT_DIR     = $$system_path($$absolute_path($$PWD))
SCRIPTS_DIR  = $$system_path($$absolute_path(../scripts))
SOURCE_TREE  = $$system_path($$absolute_path($$PWD))
QML_MATERIAL = $$system_path($$absolute_path(../qml-material/modules))

APP_TARGET               = forceSim
INSTALL_DIR              = $$system_path($$clean_path($$BUILD_TREE/ForcesSimulation))
DATA_DIR                 = $$system_path($$clean_path($$INSTALL_DIR/data))
INSTALL_LIBRARY_PATH     = $$system_path($$clean_path($$DATA_DIR/lib))
INSTALL_PLUGINS_DIR      = $$system_path($$clean_path($$DATA_DIR/plugins))
INSTALL_QML_MODULES_PATH = $$system_path($$clean_path($$DATA_DIR/qml))

QML_RELATIVE_PATH = $$clean_path($$relative_path($$INSTALL_QML_MODULES_PATH, $$INSTALL_DIR))
PLUGINS_RELATIVE_PATH = $$clean_path($$relative_path($$INSTALL_PLUGINS_DIR, $$INSTALL_DIR))

target.path = $$BUILD_TREE
TARGET = $$APP_TARGET
DESTDIR = $$INSTALL_DIR
MOC_DIR = mocdir
OBJECTS_DIR = objectsdir
RCC_DIR = rccdir

DEFINES += QML_RELATIVE_PATH=\\\"$$QML_RELATIVE_PATH\\\"
DEFINES += PLUGINS_PATH=\\\"$$PLUGINS_RELATIVE_PATH\\\"

qml_material_modules.path = $$INSTALL_QML_MODULES_PATH
qml_material_modules.files = $$QML_MATERIAL/*
INSTALLS += qml_material_modules


unix {
    # enable additional warnings
    QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast

    # get rid of Qt related warnings
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]" -isystem "$$[QT_INSTALL_HEADERS]/QtWidgets"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtXml" -isystem "$$[QT_INSTALL_HEADERS]/QtGui"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtCore"
    QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/QtQml"
}

#message(ROOT_DIR: $$ROOT_DIR)
#message(SCRIPTS_DIR: $$SCRIPTS_DIR)
#message(SOURCE_TREE: $$SOURCE_TREE)
#message(QML_MATERIAL: $$QML_MATERIAL)
#message(INSTALL_DIR: $$INSTALL_DIR)
#message(INSTALL_QML_MODULES_PATH: $$INSTALL_QML_MODULES_PATH)
#message(QML_RELATIVE_PATH: $$QML_RELATIVE_PATH)
#message(PLUGINS_RELATIVE_PATH: $$PLUGINS_RELATIVE_PATH)

include(deployment.pri)

