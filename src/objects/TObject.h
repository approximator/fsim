/*!
 * @file TObject.h
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

#ifndef TOBJECT_H
#define TOBJECT_H

#include "QQmlAutoPropertyHelpers.h"

#include <QDebug>
#include <QObject>
#include <QVector3D>

class TObject : public QObject
{
    Q_OBJECT
    QML_WRITABLE_AUTO_PROPERTY(QString, typeName)
    QML_WRITABLE_AUTO_PROPERTY(int, point_id)
    QML_WRITABLE_AUTO_PROPERTY(QVector3D, location)
    QML_WRITABLE_AUTO_PROPERTY(qreal, mass)
    QML_WRITABLE_AUTO_PROPERTY(QVector3D, force)
    QML_WRITABLE_AUTO_PROPERTY(QVector3D, engineForce)
    QML_WRITABLE_AUTO_PROPERTY(QVector3D, speed)
    QML_WRITABLE_AUTO_PROPERTY(QVector3D, acceleration)
    QML_WRITABLE_AUTO_PROPERTY(qreal, criticalRadius)
    QML_WRITABLE_AUTO_PROPERTY(bool, acceptNewPoints)

public:
    explicit TObject(const uint id, const QVector3D &initialLocation = QVector3D(), QObject *parent = 0);
    ~TObject();

    void set_acceleration(const qreal _x, const qreal _y);
    void set_speed(const qreal _x, const qreal _y);

    Q_INVOKABLE void addVisibleObject(TObject *point);
    Q_INVOKABLE const QList<TObject *> &visibleObjects() const;
    Q_INVOKABLE void clearVisibleObjectsList();

private:
    QList<TObject *> m_visibleObjects;
};

#endif  // TOBJECT_H
