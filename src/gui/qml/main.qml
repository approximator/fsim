import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Scene3D 2.0

Window {
    id: mainview
    width: 1280
    height: 768
    visible: true
    color: "#000000"

    Scene3D {
        anchors.fill: parent
        aspects: ["render", "logic", "input"]
        focus: true

        Scene {
            id: sceneRoot
        }
    }

}
