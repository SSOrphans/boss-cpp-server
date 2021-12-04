# Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"
NORM="\033[0m"

# Project Directories
PROJECT_ROOT_DIR=${HOME}/smoothstack/boss/cpp-server
PROJECT_SOURCE_DIR=${PROJECT_ROOT_DIR}/source
PROJECT_BUILD_DIR=${PROJECT_ROOT_DIR}/build

# Microservice Directories
MICROSERVICE_ROOT_DIR=/root
MICROSERVICE_SOURCE_DIR=${MICROSERVICE_ROOT_DIR}/source
MICROSERVICE_BUILD_DIR=${MICROSERVICE_ROOT_DIR}/build

# Podman Variables
PODMAN_VOLUME="${PROJECT_ROOT_DIR}:${MICROSERVICE_ROOT_DIR}"
PODMAN_OPTIONS_DEVEL="--security-opt label=disable --rm --volume ${PODMAN_VOLUME}"
PODMAN_OPTIONS_INTERACT="--privileged --rm -it --volume ${PODMAN_VOLUME}"
PODMAN_BUILD_DEVEL="podman build --tag cpp-server-devel --target development ${PROJECT_ROOT_DIR}"
PODMAN_BUILD_PROD="podman build --tag cpp-server-prod --target production ${PROJECT_ROOT_DIR}"
PODMAN_RUN_DEVEL="podman run ${PODMAN_OPTIONS_DEVEL} cpp-server-devel"
PODMAN_RUN_PROD="podman run cpp-server-prod"
PODMAN_RUN_INTERACT="podman run ${PODMAN_OPTIONS_INTERACT} cpp-server-devel"
PODMAN_CLEAN_DEVEL="podman image rm cpp-server-devel"
PODMAN_CLEAN_PROD="podman image rm cpp-server-prod"
PODMAN_PRUNE_IMAGES="podman image prune"
