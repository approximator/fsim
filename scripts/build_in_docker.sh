#!/bin/bash

THIS_DIR=$(cd $(dirname $0) && pwd)

export APP_DIR_NAME=Forces_Simulation
export APP_NAME=fsim
export SRC_DIR=$(cd "$THIS_DIR"/../ && pwd)
export INSTALL_DIR=/tmp/Forces_Simulation/docker
export SCRIPTS_DIR=${SRC_DIR}/modules/Qt-Qbs-Application/scripts

"$SCRIPTS_DIR/build_in_docker.sh"
