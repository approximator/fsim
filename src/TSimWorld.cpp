/*!
 * @file TSimWorld.cpp
 *
 * @brief Representation of a simulation world that contains points
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
#include <cmath>

#include "TSimWorld.h"
#include "experiment_runner.h"
#include "objects/TObstacle.h"
#include "objects/TSphere.h"
#include "objects/TTarget.h"

TSimWorld::TSimWorld(QObject* parent)
    : QObject(parent)
    , m_model(new TObjectsModel(this, "x", "y"))
    , m_selectedPoint(nullptr)
    , m_gravity(100)
    , m_damperCoefficient(0.4)
{
    qRegisterMetaType<TObject*>("TObject*");

    connect(this, &TSimWorld::damperCoefficientChanged, [this]() { qDebug() << "Damper = " << damperCoefficient(); });
}

TObject* createObject(const QString& type, const QVector3D& location, int id, TObjectsModel* model)
{
    if (type == "Object")
        return new TObject(id, location, model);

    if (type == "Sphere")
        return new TSphere(id, location, model);

    if (type == "Obstacle")
        return new TObstacle(id, location, model);

    if (type == "Target")
        return new TTarget(id, location, model);

    throw std::runtime_error("Unknown type");
}

TObject* TSimWorld::addObject(const QString& type, const QVector3D& location)
{
    auto newPoint = createObject(type, location, m_model->count(), m_model);

    for (const auto& point : *m_model) {
        newPoint->addVisibleObject(point);
        point->addVisibleObject(newPoint);
    }
    m_model->append(newPoint);
    return newPoint;
}

void TSimWorld::update()
{
    m_interactionFunc(this);
}

void TSimWorld::clean()
{
    m_model->clear();
}

void TSimWorld::setInteractionFunction(const TSimWorld::TInteractionFunction& func)
{
    m_interactionFunc = func;
}
