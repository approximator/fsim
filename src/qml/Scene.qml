import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

import QtQuick 2.0
import sim.world 1.0

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, 20.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )

        aspectRatio: width / height
    }

//    FirstPersonCameraController { camera: camera }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }
        },
        InputSettings { }
    ]

    World {
        id: world

        onSelectedPointChanged: {
            pointParametersDialog.point = selectedPoint
            pointParametersDialog.show()
        }
        Component.onCompleted: {
            var point = world.addPoint(2, 3.94)
            point = world.addPoint(3, 4.94)
            point = world.addPoint(4, 5.94)
            point = world.addPoint(-5, -10)
            point = world.addPoint(5, -10)

            point = world.addPoint(0, 0)
            point.criticalRadius = 2
            point.mass = 20
            point.clearVisibleObjectsList()
            point.acceptNewPoints = false
            world.damperCoefficient = 3
        }
    }

    NodeInstantiator {
        model: world.model
        delegate: Body {
            parent: sceneRoot
            position: Qt.vector3d(model.x, model.y, 0)
        }
    }

    Timer {
        id: timer;
        interval: 50;
        running: true;
        repeat: true

        onTriggered: {
            world.update()
        }
    }
}
