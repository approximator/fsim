/*!
 * @file experiment_runner.h
 *
 * @brief This file is used whet we want just run a few experiments without starting the UI
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
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

#ifndef EXPERIMENT_RUNNER_H
#define EXPERIMENT_RUNNER_H

#ifdef JUST_RUN_EXPERIMENTS

#include "TSimWorld.h"

#include <QDir>
#include <QString>
#include <fstream>

#define DEFAULT_OUT_FILE "/tmp/fsim_experiments_data"
#define LOG_EXPERIMENT_DATA(data)                                                                                      \
    do {                                                                                                               \
        auto filename = std::string(qgetenv("FSIM_DATA_FILE_NAME").constData());                                       \
        if (filename.empty()) {                                                                                        \
            filename = DEFAULT_OUT_FILE;                                                                               \
        }                                                                                                              \
        std::ofstream outfile(filename, std::ios_base::out | std::ios_base::app);                                      \
        outfile << data << std::endl;                                                                                  \
        outfile.close();                                                                                               \
    } while (0)

#ifndef DAMPERS
#define DAMPERS 0.1, 1, 3, 5
#endif

class ExperimentRunner
{
public:
    int run()
    {
        auto filename = QString(qgetenv("FSIM_DATA_FILE_NAME").constData());
        if (filename.isEmpty()) {
            filename = DEFAULT_OUT_FILE;
        }
        qDebug() << "Output file: " << filename;
        QDir().remove(filename);

        TSimWorld world;
        static const double dampers[]   = { DAMPERS };
        static const int experimentsNum = sizeof(dampers) / sizeof(dampers[0]);

        int ticsNum = 12000;
        for (int experiment = 0; experiment < experimentsNum; ++experiment) {
            world.set_damperCoefficient(dampers[experiment]);

            world.model()->clear();
            auto point = world.addPoint(12, 3.94);
            point      = world.addPoint(14, 4.94);
            point->clearVisibleObjectsList();
            for (int tic = 0; tic < ticsNum; ++tic) {
                world.update();
            }
        }
        return 0;
    }
};

#else
#define LOG_EXPERIMENT_DATA(data)
#endif  // JUST_RUN_EXPERIMENTS

#endif  // EXPERIMENT_RUNNER_H
