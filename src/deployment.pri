android-no-sdk {
    target.path = /data/user/qt
    export(target.path)
    INSTALLS += target
} else:android {
    x86 {
        target.path = /libs/x86
    } else: armeabi-v7a {
        target.path = /libs/armeabi-v7a
    } else {
        target.path = /libs/armeabi
    }
    export(target.path)
    INSTALLS += target
} else:unix {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}

export(INSTALLS)

deploy.commands = python -u $$shell_quote($$system_path($$SCRIPTS_DIR/deployqt.py))      \
                                $$shell_quote($$system_path($$INSTALL_DIR/$$APP_TARGET)) \
                                $$shell_quote($$INSTALL_DIR)                             \
                                $$shell_quote($$DATA_DIR)                                \
                                $$shell_quote($$INSTALL_LIBRARY_PATH)                    \
                                $$shell_quote($$system_path($(QMAKE)))                   \
                                $$BUILD_TYPE
deploy.depends = install

QMAKE_EXTRA_TARGETS += deploy

