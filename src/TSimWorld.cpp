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

TSimWorld::TSimWorld(QObject *parent)
    : QObject(parent)
    , m_model(new TPointsModel(this, "x", "y"))
    , m_selectedPoint(nullptr)
    , m_gravity(100)
    , m_damperCoefficient(0.4)
{
    qRegisterMetaType<TPoint *>("TPoint*");

    connect(this, &TSimWorld::damperCoefficientChanged, [this]() { qDebug() << "Damper = " << damperCoefficient(); });
}

TPoint *TSimWorld::addPoint(qreal _x, qreal _y)
{
    auto newPoint = new TPoint(m_model->count(), _x, _y, m_model);
    for (const auto &point : *m_model) {
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

void TSimWorld::setInteractionFunction(const TSimWorld::TInteractionFunction &func)
{
    m_interactionFunc = func;
}
