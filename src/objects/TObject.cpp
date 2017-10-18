/*!
 * @file TObject.cpp
 *
 * @brief TObject represents an object with it's own mass
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin (alex@nls.la)
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

#include "TObject.h"

#include <QDebug>
#include <QtMath>

TObject::TObject(const uint _id, const QVector3D &initialLocation,
                 QObject *parent)
    : QObject(parent)
    , m_typeName("Object")
    , m_object_id(_id)
    , m_location(initialLocation)
    , m_mass(1.0)
    , m_engineForce(0, 0, 0)
    , m_speed(0, 0, 0)
    , m_acceleration(0, 0, 0)
    , m_criticalRadius(1)
    , m_acceptNewPoints(true)
    , m_force(0, 0, 0)
    , m_visibleObjects()
{
    qDebug() << "Added point [" << object_id() << "]: " << location();
}

TObject::~TObject()
{
    qDebug() << "Deleted point: " << object_id();
}

void TObject::computeActingForces()
{
    auto resultingForce = engineForce();

    for (const auto &obj : m_visibleObjects) {
        const auto distance = location().distanceToPoint(obj->location());             // distance
        const auto forceDirection = (obj->location() - location()).normalized();       // direction
        const auto crSum = (criticalRadius() + obj->criticalRadius());                 // distance between objects
        const auto attractiveForce = mass() * obj->mass() / qPow(distance, 2);         // mi * mj / d^2
        const auto repulsiveForce = crSum * mass() * obj->mass() / qPow(distance, 3);  // Rcr * mi * mj / d^3
        const auto forceMagnitude = (attractiveForce - repulsiveForce) * 100;          // TODO: gravity
        resultingForce += forceDirection * forceMagnitude;                             // Fi = Fi + Fij
    }
    set_force(resultingForce);
}

void TObject::addVisibleObject(TObject *point)
{
    if (m_acceptNewPoints)
        m_visibleObjects.append(point);
}

const QList<TObject *> &TObject::visibleObjects() const
{
    return m_visibleObjects;
}

void TObject::clearVisibleObjectsList()
{
    m_visibleObjects.clear();
}

QVector3D TObject::force()
{
    computeActingForces();
    return m_force;
}

bool TObject::set_force(const QVector3D &newForce)
{
    if (m_force != newForce) {
        m_force = newForce;
        emit forceChanged();
        return true;
    } else {
        return false;
    }
}
