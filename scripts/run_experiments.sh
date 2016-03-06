#!/bin/bash
#
# Copyright © 2016 Oleksii Aliakin. All rights reserved.
# Author: Oleksii Aliakin (alex@nls.la).
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


SCRIPT_DIR=$(cd $(dirname $0) && pwd)
SRC_DIR=$(cd ${SCRIPT_DIR}/../ && pwd)
FSIM_INSTALL_DIR="/tmp/fsim/fsim_install"

export FSIM_DATA_FILE_NAME="/tmp/fsim_data"

qbs run --file ${SRC_DIR}                      \
        --command-echo-mode summary            \
        --clean-install-root                   \
        --build-directory /tmp/fsim/fsim_build \
        qbs.installRoot:${FSIM_INSTALL_DIR}    \
        project.justRunExperiments:true        \
        release

python ${SCRIPT_DIR}/plot.py --input ${FSIM_DATA_FILE_NAME} --out ${FSIM_INSTALL_DIR}
