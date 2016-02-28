/*!
 * @file TPoint.h
 *
 * @brief TPoint represents a point with it's own mass
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

#ifndef TPOINT_H
#define TPOINT_H

#include "QQmlVarPropertyHelpers.h"

#include <QDebug>
#include <QObject>
#include <QVector2D>

class TPoint : public QObject
{
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(int, point_id)
    QML_WRITABLE_VAR_PROPERTY(qreal, x)
    QML_WRITABLE_VAR_PROPERTY(qreal, y)
    QML_WRITABLE_VAR_PROPERTY(qreal, mass)
    QML_WRITABLE_VAR_PROPERTY(bool, obstacle)
    QML_WRITABLE_VAR_PROPERTY(QVector2D, force)
    QML_WRITABLE_VAR_PROPERTY(QVector2D, ownForce)
    QML_WRITABLE_VAR_PROPERTY(QVector2D, speed)
    QML_WRITABLE_VAR_PROPERTY(QVector2D, acceleration)
    QML_WRITABLE_VAR_PROPERTY(qreal, criticalRadius)

    QML_WRITABLE_VAR_PROPERTY(bool, acceptNewPoints)

public:
    explicit TPoint(const uint id, const qreal _x, const qreal _y, QObject* parent = 0);
    ~TPoint();

    QVector2D position() const;
    void set_acceleration(const qreal _x, const qreal _y);
    void set_speed(const qreal _x, const qreal _y);

    Q_INVOKABLE void addVisibleObject(TPoint* point);
    Q_INVOKABLE const QList<TPoint*>& visibleObjects() const;
    Q_INVOKABLE void clearVisibleObjectsList();

private:
    QList<TPoint*> m_visibleObjects;
};

#endif // TPOINT_H
