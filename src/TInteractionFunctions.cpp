/*!
 * @file TInteractionFunctions.cpp
 *
 * @brief Different interaction functions
 *
 *
 * Copyright © 2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "TInteractionFunctions.h"
#include "TSimWorld.h"
#include "experiment_runner.h"

#include <QtMath>

TInteractionFunctions::TInteractionFunctions()
{
}

inline qreal rungeKutta(const qreal h, const qreal val)
{
    const qreal k1 = h * val;
    const qreal k2 = h * val + k1 / 2;
    const qreal k3 = h * val + k2 / 2;
    const qreal k4 = h * val + k3;
    const qreal d  = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return d;
}

int TInteractionFunctions::polinomial(TSimWorld *world)
{
    for (int i = 0; i < 10; ++i) {
        // Update forces and locations
        for (auto &point : *(world->model())) {

            point->set_force(QVector3D(0, 0, 0));
            for (auto &otherPoint : point->visibleObjects()) {
                if (point == otherPoint) {
                    continue;
                }

                const qreal distance = point->location().distanceToPoint(otherPoint->location());  // distance
                QVector3D Fij        = (otherPoint->location() - point->location()).normalized();  // Force direction

                const qreal criticalRadius = (point->criticalRadius() + otherPoint->criticalRadius());

                qreal attractiveForce = 0;
                attractiveForce       = point->mass() * otherPoint->mass() / qPow(distance, 2);  //        mi * mj / d^2

                const qreal repulsiveForce
                    = criticalRadius * point->mass() * otherPoint->mass() / qPow(distance, 3);  //  Rcr * mi * mj / d^3
                const qreal forceMagnitude = world->gravity() * (attractiveForce - repulsiveForce);
                Fij *= forceMagnitude;                   // forceDirection * forceMagnitude
                point->set_force(point->force() + Fij);  // Fi = Fi + Fij

                if (point->point_id() == 0) {
                    LOG_EXPERIMENT_DATA("distance:" << distance << " force:" << forceMagnitude
                                                    << " acceleration:" << point->acceleration().length() << " speed:"
                                                    << point->speed().length() << " gravity:" << world->gravity()
                                                    << " damper:" << world->damperCoefficient());
                }
            }

            point->set_force(point->force() + point->engineForce());

            // Update point location

            const qreal udx = -world->damperCoefficient() * point->speed().x();
            const qreal udy = -world->damperCoefficient() * point->speed().y();
            const qreal udz = -world->damperCoefficient() * point->speed().z();

            point->set_acceleration(  // d^2x/dt^2 = 1/m * (F + (u * dx/dt))
                QVector3D((point->force().x() + udx) / point->mass(), (point->force().y() + udy) / point->mass(),
                    (point->force().z() + udz) / point->mass()));

            const qreal h = 0.0005;
            point->set_speed(QVector3D(point->speed().x() + rungeKutta(h, point->acceleration().x()),
                point->speed().y() + rungeKutta(h, point->acceleration().y()),
                point->speed().z() + rungeKutta(h, point->acceleration().z())));

            point->set_location(QVector3D(point->location().x() + rungeKutta(h, point->speed().x()),
                point->location().y() + rungeKutta(h, point->speed().y()),
                point->location().z() + rungeKutta(h, point->speed().z())));
        }
    }
    return 0;
}

// int TInteractionFunctions::linear(TSimWorld *world)
//{
//    for (int i = 0; i < 10; ++i) {
//        // Update forces and locations
//        for (auto &point : *(world->model())) {
//            point->set_force(QVector2D(0, 0));
//            for (auto &otherPoint : point->visibleObjects()) {
//                if (point == otherPoint) {
//                    continue;
//                }

//                const qreal distance =
//                point->location().distanceToPoint(otherPoint->location());  //
//                distance
//                QVector2D Fij        = (otherPoint->location() -
//                point->location()).normalized();  // Force direction

//                const qreal criticalRadius = (point->criticalRadius() +
//                otherPoint->criticalRadius());

//                qreal attractiveForce = 0;
//                if (!otherPoint->obstacle())
//                    attractiveForce = 3 * distance + criticalRadius;  //

//                const qreal repulsiveForce = 2 * distance + criticalRadius; //
//                const qreal forceMagnitude = -world->gravity() *
//                (attractiveForce - repulsiveForce);
//                Fij *= forceMagnitude;                   // forceDirection *
//                forceMagnitude
//                point->set_force(point->force() + Fij);  // Fi = Fi + Fij

//                if (point->point_id() == 0) {
//                    LOG_EXPERIMENT_DATA("distance:" << distance << " force:"
//                    << forceMagnitude
//                                                    << " acceleration:" <<
//                                                    point->acceleration().length()
//                                                    << " speed:"
//                                                    << point->speed().length()
//                                                    << " gravity:" <<
//                                                    world->gravity()
//                                                    << " damper:" <<
//                                                    world->damperCoefficient());
//                }
//            }

//            point->set_force(point->force() + point->ownForce());

//            // Update point location

//            const qreal udx = -world->damperCoefficient() *
//            point->speed().x();
//            const qreal udy = -world->damperCoefficient() *
//            point->speed().y();

//            point->set_acceleration(  // d^2x/dt^2 = 1/m * (F + (u * dx/dt))
//                QVector2D((point->force().x() + udx) / point->mass(),
//                (point->force().y() + udy) / point->mass()));

//            const qreal h = 0.0005;
//            point->set_speed(QVector2D(point->speed().x() + rungeKutta(h,
//            point->acceleration().x()),
//                point->speed().y() + rungeKutta(h,
//                point->acceleration().y())));

//            point->set_location(QVector2D(point->location().x() +
//            rungeKutta(h, point->speed().x()),
//            (point->location().y() + rungeKutta(h, point->speed().y()))));
//        }
//    }
//    return 0;
//}
