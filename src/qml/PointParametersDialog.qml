import QtQuick 2.4
import QtQuick.Controls 1.3 as QuickControls
import Material 0.2
import Material.Extras 0.1

Dialog {
    property QtObject point: null

    title: "Object parameters"

    onPointChanged: {
        massSlider.value = point.mass
        visibleObjectsRepeater.model = point.visibleObjects()
        visibleObjectsRepeater.update()
    }

    Label {
        style: "subheading"
        text: "Selected point: " + (point ? point.point_id : "(none)")
    }

    Label {
        text: "mass"
    }
    Slider {
        id: massSlider
        numericValueLabel: true
        tickmarksEnabled: true
        stepSize: 5
        minimumValue: 10
        maximumValue: 1000
//        onValueChanged: {
//            point.mass = value
//        }
    }

    Column {
        id: contentColumn
        Repeater {
            id: visibleObjectsRepeater
            model: null
            delegate: Text {
                //width: flickable.width
                wrapMode: Text.Wrap
                font.pixelSize: 16
                textFormat: Text.RichText
                text: aaa
            }
        }
    }
}

