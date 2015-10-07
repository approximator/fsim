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
                ctx.save()

                var x = world.pointXScreenPos(i)
                var y = world.pointYScreenPos(i)
                ctx.beginPath()
                ctx.translate(x, y)
                ctx.arc(0, 0, 10, 0, 2 * Math.PI, false)
                ctx.fillStyle = 'green'
                ctx.fill()
                ctx.lineWidth = 5
                ctx.strokeStyle = '#003300'
                ctx.stroke()

                ctx.resetTransform()
                ctx.restore()
            }
        }

        onWidthChanged: screen.width = width
        onHeightChanged: screen.height = height
    }

    MouseArea {
        property int prevX: 0
        property int prevY: 0
        property int prevXOffset: 0
        property int prevYOffset: 0

        anchors.fill: parent
        hoverEnabled: false

        onPressed: {
            prevX = mouse.x
            prevY = mouse.y
            prevXOffset = canvas.screen.offsetX
            prevYOffset = canvas.screen.offsetY
        }

        onPositionChanged: {
            canvas.screen.offsetX = prevXOffset + mouse.x - prevX
            canvas.screen.offsetY = prevYOffset + mouse.y - prevY
            canvas.requestPaint();
        }

        onWheel: {
            if (wheel.angleDelta.y > 0)
                canvas.screen.scale += 1
            else
                canvas.screen.scale -= 1
        }

        onDoubleClicked: {
            world.addPoint(world.xScreenToWorld(mouse.x), world.yScreenToWorld(mouse.y))
        }
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

    Timer {
        id: timer;
        interval: 100;
        running: true;
        repeat: true
        onTriggered: {
            world.update();
            canvas.requestPaint();
        }
    }
}

