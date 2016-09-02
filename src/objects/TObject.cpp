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

TObject::TObject(const uint _id, const QVector3D &initialLocation, QObject *parent)
    : QObject(parent)
    , m_typeName("Object")
    , m_point_id(_id)
    , m_location(initialLocation)
    , m_mass(1.0)
    , m_force()
    , m_engineForce(0, 0, 0)
    , m_speed(0, 0, 0)
    , m_acceleration(0, 0, 0)
    , m_criticalRadius(1)
    , m_acceptNewPoints(true)
    , m_visibleObjects()
{
    qDebug() << "Added point [" << point_id() << "]: " << location();
}

TObject::~TObject()
{
    qDebug() << "Deleted point: " << point_id();
}

void TObject::set_acceleration(const qreal _x, const qreal _y)
{
    m_acceleration.setX(_x);
    m_acceleration.setY(_y);
}

void TObject::set_speed(const qreal _x, const qreal _y)
{
    m_speed.setX(_x);
    m_speed.setY(_y);
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
