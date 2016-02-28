/*!
 * @file TSimWorld.h
 *
 * @brief Representation of a simulation world that contains points
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

#ifndef SIMWORLD_H
#define SIMWORLD_H

#include "QQmlObjectListModel.h"
#include "TPoint.h"
#include "TScreen.h"

#include <QAbstractListModel>
#include <QList>
#include <QObject>

typedef QQmlObjectListModel<TPoint> TPointsModel;

class TSimWorld : public QObject
{
    Q_OBJECT
    QML_READONLY_VAR_PROPERTY(TPointsModel *, model)
    QML_READONLY_VAR_PROPERTY(TScreen *, screen)
    QML_WRITABLE_VAR_PROPERTY(TPoint *, selectedPoint)
    QML_WRITABLE_VAR_PROPERTY(qreal, gravity)
    QML_WRITABLE_VAR_PROPERTY(qreal, damperCoefficient)

public:
    explicit TSimWorld(QObject *parent = 0);

    Q_INVOKABLE TPoint *getPointAt(qreal _x, qreal _y) const;

    Q_INVOKABLE qreal xToScreen(qreal xPos) const;
    Q_INVOKABLE qreal yToScreen(qreal yPos) const;
    Q_INVOKABLE qreal xToWorld(qreal xPos) const;
    Q_INVOKABLE qreal yToWorld(qreal yPos) const;

    Q_INVOKABLE TPoint *addPoint(qreal _x, qreal _y);
    Q_INVOKABLE void update();
    Q_INVOKABLE void clean();
    Q_INVOKABLE QVector2D forceAt(qreal _x, qreal _y);

private:
    TSimWorld(const TSimWorld &other) = delete;
    TSimWorld &operator=(const TSimWorld &other) = delete;

public slots:
};

#endif // SIMWORLD_H
