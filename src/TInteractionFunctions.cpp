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

inline QVector3D rungeKutta(const qreal h, const QVector3D &val)
{
    const auto k1 = h * val;
    const auto k2 = h * val + k1 / 2;
    const auto k3 = h * val + k2 / 2;
    const auto k4 = h * val + k3;
    const auto d = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return d;
}

int TInteractionFunctions::polinomial(TSimWorld *world)
{
    for (int i = 0; i < 10; ++i) {
        // Update forces and locations
        for (auto &obj : *(world->model())) {
            // d^2x/dt^2 = 1/m * (F + (u * dx/dt))
            const auto dampedSpeed = obj->speed() * -world->damperCoefficient();
            obj->set_acceleration((obj->force() + dampedSpeed) / obj->mass());

            const qreal h = 0.0005;
            obj->set_speed(obj->speed() + rungeKutta(h, obj->acceleration()));
            obj->set_location(obj->location() + rungeKutta(h, obj->speed()));
        }
    }
    return 0;
}
