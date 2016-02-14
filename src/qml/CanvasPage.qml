import QtQuick 2.0
import Material 0.1
import sim.world 1.0
import QtQuick.Layouts 1.1
import Material.ListItems 0.1 as ListItem

Page {
    title: "Forces simulation - " + selectedConfiguration
    id: page

    backgroundColor: Theme.primaryDarkColor
    actions: [
        Action {
            id: actionPause
            iconName: checked ? "av/play_circle_outline" : "av/pause_circle_outline"
            name: checked ? "Start simulation" : "Pause simulation"
            checkable: true
            onTriggered: checked = !checked
            enabled: true
        },
        Action {
            iconName: "av/games"
            name: "Auto center"
            hoverAnimation: true
            enabled: true
        }
    ]

    property var configurations: [
        "Blank", "Two points", "Three points", "Four points", "Four points with obstacle",
        "Two points moving"
    ]

    property string selectedConfiguration: configurations[0]

    onSelectedConfigurationChanged: setupConfiguration(selectedConfiguration)

    backAction: navDrawer.action

    World {
        id: world
        damperCoefficient: damperSlider.value

        onSelectedPointChanged: {
            pointParametersDialog.point = selectedPoint
            pointParametersDialog.show()
        }
        Component.onCompleted: damperCoefficient = 400
    }

    PointParametersDialog {
        id: pointParametersDialog
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        property QtObject screen: world.screen
        onWidthChanged: screen.width = width
        onHeightChanged: screen.height = height

        onPaint: {
            var ctx = getContext("2d")
            ctx.fillStyle = '#222222';
            ctx.fillRect(0, 0, width, height)
            drawGrid(ctx)
            drawPoints(ctx)
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

            onDoubleClicked: world.addPoint(world.xToWorld(mouse.x), world.yToWorld(mouse.y))

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

//        property int currentTic: 0
//        property int currentExperiment: -1
//        property int maxTics: 0
//        property var dampers: [10, 400, 500, 600, 800]

        onTriggered: {
            if (!actionPause.checked)
                world.update();
            canvas.requestPaint();
        }
    }

    NavigationDrawer {
        id: navDrawer
        enabled: true

        Flickable {
            anchors.fill: parent
            contentHeight: Math.max(content.implicitHeight, height)

            Column {
                id: content
                anchors.fill: parent

                Repeater {
                    model: configurations
                    delegate: ListItem.Standard {
                        backgroundColor: Theme.primaryDarkColor
                        text: modelData
                        selected: modelData == selectedConfiguration
                        onClicked: {
                            page.selectedConfiguration = modelData
                            navDrawer.close()
                        }
                    }
                }
            }
        }
    }

    Label {
        font.family: "Roboto"
        font.weight: Font.Bold
        font.pixelSize: Units.dp(40)
        text: "Simulation paused"
        color: Theme.primaryColor
        visible: actionPause.checked
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            margins: Units.dp(16)
        }
    }

    View {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: Units.dp(200)
        height: Math.max(column.implicitHeight, height)
        anchors.margins: 20
        Column {
            id: column
            width: parent.width
            Label {
                text: "World parameters:"
                color: Theme.light.textColor
            }

            RowLayout {
                width: parent.width
                Label {
                    height: damperSlider.height
                    color: Theme.light.textColor
                    text: "Damper:"
                }
                Slider {
                    id: damperSlider
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    numericValueLabel: true
                    tickmarksEnabled: true
                    stepSize: 10
                    minimumValue: 10
                    maximumValue: 1100
                    value: world.damperCoefficient
                }
            }
        }
    }

    function setupConfiguration(configurationName) {
        world.clean();
        canvas.screen.offsetX = 0
        canvas.screen.offsetY = 0
        //world.damperCoefficient = 8000

        switch(configurationName) {
        case "Two points":
            var point = world.addPoint(10, 3.94)
            point = world.addPoint(14, 4.94)
            point.clearVisibleObjectsList()
            world.damperCoefficient = 10

            break;

        case "Three points":
            var point = world.addPoint(10, 3.94)
            point = world.addPoint(14, 4.94)
            point = world.addPoint(14, 6.94)
            break;

        case "Four points":
            var point = world.addPoint(2, 3.94)
            point = world.addPoint(3, 4.94)
            point = world.addPoint(4, 5.94)

            point = world.addPoint(11, 4.94)
            point.criticalRadius = 3
            point.mass = 10000
            point.clearVisibleObjectsList()
            point.acceptNewPoints = false
            break;

        case "Four points with obstacle":
            var point = world.addPoint(1, 2.94)
            world.addPoint(1, 3.94)
            point = world.addPoint(1, 4.94)
            point = world.addPoint(1, 5.94)

            // target
            point = world.addPoint(10, 4.94)
            point.criticalRadius = 8
            point.mass = 100000
            point.clearVisibleObjectsList()
            point.acceptNewPoints = false
            point.ownForce.x = 50000000

            // obstacle
            point = world.addPoint(15, 4.94)
            point.criticalRadius = 0.7
            point.mass = 200
            point.clearVisibleObjectsList()
            point.acceptNewPoints = false
            point.obstacle = true
            break;

        case "Two points moving":
            var point = world.addPoint(5, 0.8)
            point.ownForce.y = 500000
            point.mass = 200

            point = world.addPoint(15, 0.8)
            point.ownForce.y = 500000
            point.mass = 200
            break;

        case "Blank":  // fall through
        default:
            world.clean();
        }
    }

    function drawPoints(ctx) {
        var num = world.model.rowCount()
        if (num <= 0)
        {
            return
        }

        var pointSize = 5
        for (var i = 0; i < num; ++i)
        {
            ctx.save()

            var point = world.model.get(i)
            var x = world.xToScreen(point.x)
            var y = world.yToScreen(point.y)
            var circleRadius = world.model.get(i).criticalRadius * canvas.screen.scale

            ctx.translate(x, y)
            ctx.beginPath()
            ctx.strokeStyle = 'red'
            ctx.arc(0, 0, circleRadius, 0, 2 * Math.PI, false)
            ctx.stroke();

            ctx.beginPath()
            ctx.fillStyle = 'green'
            ctx.arc(0, 0, pointSize, 0, 2 * Math.PI, false)
            if (point === world.selectedPoint)
                ctx.fillStyle = 'yellow'
            ctx.fill()

            ctx.resetTransform()
            ctx.restore()
        }
    }

    function drawGrid(ctx) {
        var gridSize = 50

        ctx.beginPath()
        ctx.lineWidth = 0.8
        ctx.fillStyle = "yellow";
        var x = canvas.screen.offsetX % gridSize
        var y = canvas.screen.offsetY % gridSize
        for (; x < canvas.width; x += gridSize) {
            ctx.moveTo(x, 0)
            ctx.lineTo(x, canvas.height)
            ctx.fillText(world.xToWorld(x).toFixed(4), x - 10, 15);
        }
        for (; y < canvas.height; y += gridSize) {
            ctx.moveTo(0, y)
            ctx.lineTo(canvas.width, y)
            ctx.fillText(world.yToWorld(y).toFixed(4), 5, y);
        }
        ctx.strokeStyle = "gray"
        ctx.stroke()
    }
}
