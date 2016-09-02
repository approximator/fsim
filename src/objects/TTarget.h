/*!
 * @file TTarget.h
 *
 * @brief TTarget represents a point with it's own mass
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

#ifndef TTARGET_H
#define TTARGET_H

#include "TObject.h"

class TTarget : public TObject
{
    Q_OBJECT

public:
    explicit TTarget(const uint id, const QVector3D& initialLocation = QVector3D(), QObject* parent = 0);
    ~TTarget();
};

#endif  // TTARGET_H
