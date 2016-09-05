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

    FirstPersonCameraController { camera: camera }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: Qt.rgba(0.5, 0.7, 1, 1)
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
            var point = world.addObject("Sphere", Qt.vector3d(2, 3.94, -5))
            point = world.addObject("Sphere", Qt.vector3d(3, 4.94, 1))
            point = world.addObject("Sphere", Qt.vector3d(4, 5.94, 5))
            point = world.addObject("Sphere", Qt.vector3d(-2, -10, 1))
            point = world.addObject("Sphere", Qt.vector3d(2, -10, 1))

            point = world.addObject("Obstacle", Qt.vector3d(0, -5, 0.5))

            point = world.addObject("Target", Qt.vector3d(0, 0, 0))
            point.criticalRadius = 2
            point.mass = 20
            world.damperCoefficient = 3
        }
    }

    NodeInstantiator {
        model: world.model
        delegate: Entity {
            id: factoryItem
            Component.onCompleted: {
                var component = Qt.createComponent(Qt.resolvedUrl(model.typeName + ".qml"))
                var obj = component.createObject(factoryItem);
                obj.position = Qt.binding(function() { return model.location });
            }
        }
    }

    Timer {
        id: timer;
        interval: 50;
        running: true;
        repeat: true

        onTriggered: {
            world.update()
            // console.log("Update")
        }
    }
}
