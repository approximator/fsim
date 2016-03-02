#!/usr/bin/env python

# Copyright © 2016 Oleksii Aliakin. All rights reserverd.
# Author: Oleksii Aliakin (alex@nls.la)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import matplotlib.pyplot as plt


def load_file(file_name):
    experiments = {}
    prev_experiment = 0
    with open(file_name, 'r') as data_file:
        for line in data_file:
            if len(line) < 1:
                continue
            temp_data = {}
            for data in line.split(' '):
                key, value = data.split(':')
                # print(key + '=' + value)
                temp_data[key] = float(value)
            current_experiment = temp_data['damper']

            if prev_experiment != current_experiment:
                prev_experiment = current_experiment
                experiments[current_experiment] = {}
            for key, value in temp_data.items():
                # print(key, value)
                if not experiments[current_experiment].get(key, None):
                    experiments[current_experiment][key] = []
                experiments[current_experiment][key].append(value)
    return experiments


def plot_by_experiment(experiments):
    for key, experiment in experiments.items():
        plt.figure()

        distance = experiment['distance']
        force = experiment['force']
        speed = experiment['speed']

        time = range(len(force))

        print(len(force), len(distance), len(time))
        # distance = map(lambda x: x / max(distance), distance)
        # force = map(lambda x: x / max(force), force)
        plt.plot(time, distance, '-r', label='Distance')
        # plt.plot(time, force, '-g', label='Force')
        plt.plot(time, speed, '-g', label='Speed')

        plt.grid()
        plt.legend(loc='upper right')
        plt.xlabel('Nodes removed')
        plt.ylabel('Max connected component')
        plt.title('Graph resilience under random order attack')

        plt.savefig('/tmp/damper_{}.svg'.format(key))


def plot_on_one(experiments):
    first_experiment = None
    for exp in experiments:
        first_experiment = exp
        break

    for param_name in first_experiment.keys():
        plt.figure()
        for key, experiment in experiments.items():
            param_data = experiment[param_name]
            gravity = experiment['gravity'][0]
            damper = experiment['damper'][0]
            time = range(len(param_data))

            # distance = map(lambda x: x / max(distance), distance)
            # force = map(lambda x: x / max(force), force)
            plt.plot(time, param_data, '-', label='Damper = {}'.format(damper))

            plt.grid()
            plt.legend(loc='upper right')
            plt.xlabel('Time')
            plt.ylabel(param_name)
            plt.title('Title')

        plt.savefig('/tmp/{}.svg'.format(param_name))

if __name__ == '__main__':
    # plot_by_experiment(load_file('/tmp/points_data'))

    plot_on_one(load_file('/tmp/fsim_experiments_data'))
