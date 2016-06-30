import QtQuick 2.0
import QtQuick.Scene3D 2.0

Item {
    id: mainview
    width: 1280
    height: 768
    visible: true

    Scene3D {
        anchors.fill: parent
        aspects: ["render", "logic", "input"]
        focus: true

        Scene {
            id: sceneRoot
        }
    }

}



