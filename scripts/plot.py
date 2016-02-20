
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

    for param_name in experiments[0.1].keys():
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
