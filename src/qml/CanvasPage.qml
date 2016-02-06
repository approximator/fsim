import QtQuick 2.0
import Material 0.1
import sim.world 1.0

Page {
    title: "Forces simulation"

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
        simPaused: checkBoxPause.checked
        onSelectedPointChanged: {
            sidebar.selectedPoint = selectedPoint
        }
    }

    Canvas {
        id: canvas
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: sidebar.left
        anchors.bottom: parent.bottom

        property QtObject screen: world.screen

        onPaint: {
            var ctx = getContext("2d")

            ctx.fillStyle = '#222222';
            ctx.fillRect(0, 0, width, height)

            var num = world.model.rowCount()
            for (var i = 0; i < num; ++i)
            {
                ctx.save()

                var x = world.pointXScreenPos(i)
                var y = world.pointYScreenPos(i)
                ctx.beginPath()
                ctx.translate(x, y)
                ctx.arc(0, 0, 10, 0, 2 * Math.PI, false)
                ctx.fillStyle = 'green'
                if (world.model.get(i) === world.selectedPoint)
                    ctx.fillStyle = 'yellow'
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
                world.addPoint(world.xToWorld(mouse.x), world.yToWorld(mouse.y))
            }

            onClicked: {
                var point = world.getPointAt(world.xToWorld(mouse.x), world.yToWorld(mouse.y))
                if (point)
                    world.selectedPoint = point
            }
        }
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

    Sidebar {
        property QtObject selectedPoint: null

        onSelectedPointChanged: {
            checkBoxPointFixed.checked = (selectedPoint ? selectedPoint.fixed : false)
            labeledEditMass.value = (selectedPoint ? selectedPoint.mass : 0)
        }

        id: sidebar
        backgroundColor: Qt.lighter(Theme.primaryDarkColor)
        mode: "right"

        Column {
            CheckBox {
                id: checkBoxPause
                checked: false
                text: "Pause simulation"
                darkBackground: true
            }
            LabeledTextEdit {
                id: labeledEditDamper
                label: "Damper"
                labelWidth: Units.dp(80)
                value: world.damperCoefficient
                onEditFinished: {
                    world.damperCoefficient = parseInt(new_text)
                }
            }

            Label {
                style: "headline"
                text: "Selected point: " + (sidebar.selectedPoint ? sidebar.selectedPoint.point_id : "")
                color: Theme.dark.textColor
            }

            LabeledTextEdit {
                id: labeledEditMass
                label: "Mass"
                value: (sidebar.selectedPoint ? sidebar.selectedPoint.mass : 0)
                onEditFinished: {
                    if (sidebar.selectedPoint)
                        sidebar.selectedPoint.mass = parseInt(new_text)
                }
            }

            CheckBox {
                id: checkBoxPointFixed
                checked: false
                text: "Fixed"
                darkBackground: true
                onCheckedChanged: {
                    if (sidebar.selectedPoint)
                        sidebar.selectedPoint.fixed = checked
                }
            }
        }
    }
}

