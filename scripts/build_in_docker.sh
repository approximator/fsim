#!/bin/bash

if [ $# = 1 ]; then
   QBS_VERSION=$1
fi

SRC_DIR=$(cd $(dirname $0)/../ && pwd)
SCRIPT_NAME="$(basename \"$(test -L \"$0\" && readlink \"$0\" || echo \"$0\")\")"
ENTRY_POINT="/tmp/dock_fsim_entry_point.sh"

: ${SRC_DIR:=$(cd "${SRC_DIR}/.." && pwd)}
: ${INSTALL_DIR:="/tmp/fsim/docker"}
: ${BUILD_VARIANT:="release"}
: ${QBS_VERSION:="qbs:1.5.1.Qt5.7.0"}

echo "SRC_DIR: ${SRC_DIR}"
echo "INSTALL_DIR: ${INSTALL_DIR}"
echo "BUILD_VARIANT: ${BUILD_VARIANT}"
echo "QBS_VERSION: ${QBS_VERSION}"

mkdir -p ${INSTALL_DIR}

cat > ${ENTRY_POINT} << EOF
#!/bin/bash
groupadd -g $(getent group $USER | cut -d: -f3) $USER
useradd -m -g $USER -G sudo -N -u $UID $USER
chown -R $USER:$USER /res
/bin/su $USER -c "cd /home/prj/src && ./scripts/build.sh /home/prj/src /res/install ${BUILD_VARIANT}"

EOF
chmod +x ${ENTRY_POINT}

VOLUMES="-v ${ENTRY_POINT}:${ENTRY_POINT}:ro -v ${SRC_DIR}:/home/prj/src:ro"
VOLUMES="${VOLUMES} -v ${INSTALL_DIR}:/res"

docker run --rm --entrypoint=${ENTRY_POINT} ${VOLUMES} approximator/${QBS_VERSION}
res=$?
rm ${ENTRY_POINT}

if [ $res -ne 0 ]; then
    echo "Failed"
    exit 1
else
    echo "Build finished!"
    echo "Installed in: ${INSTALL_DIR}"
fi
