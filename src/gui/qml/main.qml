import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Scene3D 2.0

ApplicationWindow {
    id: mainview
    width: 1280
    height: 768
    visible: true
    color: "#000000"

    toolBar: ToolBar {
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    checkable: true
                    checked: true
                    text: "Run"
                }
                ToolButton {
                    text: "Add point"
                    onClicked: {
                        console.info("Add button")
                        sceneRoot.world.addObject("Sphere", Qt.vector3d(3, 4.94, 1))
                    }
                }
//                ToolButton {
//                    iconSource: "save-as.png"
//                }
                Item { Layout.fillWidth: true }
//                CheckBox {
//                    text: "Enabled"
//                    checked: true
//                    Layout.alignment: Qt.AlignRight
//                }
            }
        }

    Scene3D {
        anchors.fill: parent
        aspects: ["render", "logic", "input"]
        focus: true

        Scene {
            id: sceneRoot
        }
    }

}
