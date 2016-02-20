/*!
 * @file experimant_runner.h
 *
 * @brief This file is used whet we want just run a few experiments without starting the UI
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 20, 2016
 */
#ifndef EXPERIMENT_RUNNER_H
#define EXPERIMENT_RUNNER_H

#include "TSimWorld.h"

#include <QDir>
#include <fstream>

#ifdef JUST_RUN_EXPERIMENTS

#define DATA_FILE_NAME "/tmp/fsim_experiments_data"
#define LOG_EXPERIMENT_DATA(data)                                                                                      \
    {                                                                                                                  \
        std::ofstream outfile(DATA_FILE_NAME, std::ios_base::out | std::ios_base::app);                                \
        outfile << data << std::endl;                                                                                  \
        outfile.close();                                                                                               \
    }

class ExperimentRunner
{
public:
    int run()
    {
        QDir().remove(DATA_FILE_NAME);

        TSimWorld world;
        static const double dampers[]   = { 0.05, 0.1, 0.5, 0.7, 1 };
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
#endif // JUST_RUN_EXPERIMENTS

#endif // EXPERIMENT_RUNNER_H
