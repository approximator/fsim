import QtQuick 2.0
import Material 0.1
import sim.world 1.0

Page {
    backgroundColor: Theme.primaryDarkColor
    actions: [
        Action {
            iconName: "av/games"
            name: "Auto center"
            hoverAnimation: true
            enabled: true
        }
    ]

    World {
        id: world
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        property QtObject screen: world.screen

        onPaint: {
            var ctx = getContext("2d")

            ctx.fillStyle = '#222222';
            ctx.fillRect(0, 0, width, height)

            var num = world.rowCount()
            for (var i = 0; i < num; ++i)
            {
                var p = world.getPoint(i)
            }
        }

        onWidthChanged: screen.width = width
        onHeightChanged: screen.height = height
    }

    Slider {
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: Units.dp(32)
        }
        value: 100
        focus: true
        numericValueLabel: true
        stepSize: 1
        minimumValue: 50
        maximumValue: 200
    }
}

