/*!
 * @file TScreen.h
 *
 * @brief User screen
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

#ifndef TSCREEN_H
#define TSCREEN_H

#include "QQmlVarPropertyHelpers.h"

#include <QObject>

class TScreen : public QObject
{
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(int, x)
    QML_WRITABLE_VAR_PROPERTY(int, y)
    QML_WRITABLE_VAR_PROPERTY(int, width)
    QML_WRITABLE_VAR_PROPERTY(int, height)
    QML_WRITABLE_VAR_PROPERTY(int, scale)
    QML_WRITABLE_VAR_PROPERTY(int, offsetX)
    QML_WRITABLE_VAR_PROPERTY(int, offsetY)

public:
    explicit TScreen(QObject *parent = 0);
};

#endif // TSCREEN_H
