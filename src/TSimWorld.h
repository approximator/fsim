/*!
 * @file TSimWorld.h
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

#ifndef SIMWORLD_H
#define SIMWORLD_H

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"
#include "TInteractionFunctions.h"
#include "objects/TObject.h"

#include <QList>
#include <QObject>
#include <functional>

typedef QQmlObjectListModel<TObject> TObjectsModel;

class TSimWorld : public QObject
{
    Q_OBJECT
    QML_READONLY_AUTO_PROPERTY(TObjectsModel *, model)
    QML_WRITABLE_AUTO_PROPERTY(TObject *, selectedPoint)
    QML_WRITABLE_AUTO_PROPERTY(qreal, gravity)
    QML_WRITABLE_AUTO_PROPERTY(qreal, damperCoefficient)

public:
    typedef std::function<int(TSimWorld *)> TInteractionFunction;

    explicit TSimWorld(QObject *parent = 0);

    Q_INVOKABLE TObject *addObject(const QString &type, const QVector3D &location);
    Q_INVOKABLE void update();
    Q_INVOKABLE void clean();

    Q_INVOKABLE void setInteractionFunction(const TInteractionFunction &func);

private:
    TSimWorld(const TSimWorld &other) = delete;
    TSimWorld &operator=(const TSimWorld &other) = delete;

    TInteractionFunction m_interactionFunc = &TInteractionFunctions::polinomial;
};

#endif  // SIMWORLD_H
