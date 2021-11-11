#!/bin/bash
RED="\033[0;31m"
GREEN="\033[0;32m"
NORM="\033[0m"

function error() {
	>&2 echo -e "$@"
	exit 1
}

# Check that we have the right number of arguments.
[[ $# -lt 1 ]] && error "${RED}-- Incorrect argument count.${NORM}"
COMMAND=$1
shift

# Project directory variables.
PROJECT_ROOT_DIR="${HOME}/smoothstack/boss/cpp-server"
PROJECT_SRC_DIR="${PROJECT_ROOT_DIR}/source"
PROJECT_BUILD_DIR="${PROJECT_ROOT_DIR}/build"

# Microservice directory variables.
MICROSERVICE_ROOT_DIR="/root"
MICROSERVICE_SRC_DIR="${MICROSERVICE_ROOT_DIR}/source"
MICROSERVICE_BUILD_DIR="${MICROSERVICE_ROOT_DIR}/build"

# Describe volume mounts.
PROJECT_VOLUME="${PROJECT_ROOT_DIR}:${MICROSERVICE_ROOT_DIR}"
echo -e "${GREEN}-- Mounting ${PROJECT_VOLUME}${NORM}"

# Podman setup.
PODMAN_OPT="--security-opt label=disable --rm"
PODMAN_VOLUMES="--volume ${PROJECT_VOLUME}"
PODMAN_CMD="podman run ${PODMAN_OPT} ${PODMAN_VOLUMES} cpp-server-devel-container"

function container_build() {
	echo -e "${GREEN}-- Building devel container...${NORM}"
	podman build --tag cpp-server-devel-container --target development ${PROJECT_ROOT_DIR}
}

function container_interact() {
	echo -e "${GREEN}-- Opening container in interactive mode...${NORM}"
	podman run ${PODMAN_OPT} -it ${PODMAN_VOLUMES} cpp-server-devel-container
}

function container_deploy() {
	# TODO: Get tag name from git tag for release version.
	echo -e "${GREEN}-- Building prod container...${NORM}"
	podman build --tag boss-cpp-server --target production ${PROJECT_ROOT_DIR}
}

function conan_prepare() {
	# Make sure the conan profile is set up.
	! [[ -f "${PROJECT_ROOT_DIR}/.conan/profiles/default" ]] && (
		${PODMAN_CMD} conan profile new default --detect --force
		${PODMAN_CMD} conan profile update settings.compiler=clang default
		${PODMAN_CMD} conan profile update settings.compiler.version=12 default
		${PODMAN_CMD} conan profile update settings.compiler.libcxx=libstdc++11 default
		${PODMAN_CMD} conan profile update env.CC=/usr/bin/clang default
		${PODMAN_CMD} conan profile update env.CXX=/usr/bin/clang++ default
		${PODMAN_CMD} conan profile update env.CONAN_CPU_COUNT=6 default
	)
}

function conan_install() {
	conan_prepare
	${PODMAN_CMD} conan install --build missing --install-folder ${MICROSERVICE_BUILD_DIR} ${MICROSERVICE_ROOT_DIR}
	# ! [[ -d "${PROJECT_BUILD_DIR}" ]] && (
	# 	mkdir -p ${PROJECT_BUILD_DIR}
	# )
}

function conan_build() {
	conan_install
	${PODMAN_CMD} conan build --build-folder ${MICROSERVICE_BUILD_DIR} ${MICROSERVICE_ROOT_DIR}
}

function conan_package() {
	${PODMAN_CMD} conan package --build-folder ${MICROSERVICE_BUILD_DIR} ${MICROSERVICE_ROOT_DIR}
}

function conan_clean() {
	podman run ${PODMAN_OPT} ${PODMAN_VOLUMES} --workdir ${MICROSERVICE_BUILD_DIR} cpp-server-devel-container \
		make clean
}

function clean_all() {
	rm -rf ${PROJECT_BUILD_DIR}
}

# Check for container and build if necessary.
! podman image exists cpp-server-devel-container:latest && container_build

case ${COMMAND} in
	"interactive") container_interact;;
	"deploy") container_deploy;;
	"prepare") conan_prepare;;
	"install") conan_install;;
	"build") conan_build;;
	"package") conan_package;;
	"clean") conan_clean;;
	"purge") clean_all;;
esac
