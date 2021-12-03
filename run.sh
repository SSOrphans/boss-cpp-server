#!/bin/bash
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"
NORM="\033[0m"

function print_info() {
	echo -e "${CYAN}-- $1${NORM}"
}

function print_warn() {
	echo -e "${YELLOW}-- $1${NORM}"
}

function print_error() {
	echo -e "${RED}-- $1${NORM}"
}

function error() {
	>&2 print_error $@
	exit 1
}

# Check that we have the right number of arguments.
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

# Podman setup.
PODMAN_OPT="--security-opt label=disable --rm"
PODMAN_VOLUMES="--volume ${PROJECT_VOLUME}"
PODMAN_CMD="podman run ${PODMAN_OPT} ${PODMAN_VOLUMES} cpp-server-devel-container"

function check_profile_argument() {
	[[ -z "$1" ]] && (
		echo -e "${RED}Profile must be provided in command${NORM}\n"
		echo -e "Available profiles:"
		echo -e " + ${MAGENTA}development${NORM}"
		echo -e " + ${MAGENTA}production${NORM}"
		echo -e "Usage: ./run.sh $2 <profile>"
		exit 1
	)
}

function container_build() {
	print_info "Building devel container..."
	podman build --tag cpp-server-devel-container --target development ${PROJECT_ROOT_DIR}
}

function container_interact() {
	print_info "Opening container in interactive mode..."
	print_info "Mounting ${PROJECT_VOLUME}"
	podman run --privileged --rm -it ${PODMAN_VOLUMES} cpp-server-devel-container
}

function container_deploy() {
	# TODO: Get tag name from git tag for release version.
	print_info "Building prod container..."
	podman build --tag boss-cpp-server --target production ${PROJECT_ROOT_DIR}
}

function conan_create_profile() {
	! [ -f "${PROJECT_ROOT_DIR}/.conan/profiles/$1" ] && (
		${PODMAN_CMD} conan profile new $1
		${PODMAN_CMD} conan profile update settings.os=Linux $1
		${PODMAN_CMD} conan profile update settings.os_build=Linux $1
		${PODMAN_CMD} conan profile update settings.arch=x86_64 $1
		${PODMAN_CMD} conan profile update settings.arch_build=x86_64 $1
		${PODMAN_CMD} conan profile update settings.build_type=$2 $1
		${PODMAN_CMD} conan profile update settings.compiler=clang $1
		${PODMAN_CMD} conan profile update settings.compiler.cppstd=17 $1
		${PODMAN_CMD} conan profile update settings.compiler.version=12 $1
		${PODMAN_CMD} conan profile update settings.compiler.libcxx=libstdc++11 $1
		${PODMAN_CMD} conan profile update env.CC=/usr/bin/clang $1
		${PODMAN_CMD} conan profile update env.CXX=/usr/bin/clang++ $1
		${PODMAN_CMD} conan profile update env.CONAN_CPU_COUNT=6 $1
	)
}

function conan_prepare() {
	conan_create_profile default Debug
	conan_create_profile development Debug
	conan_create_profile production Release
}

function conan_install() {
	conan_prepare

	# Make sure we are provided a profile.
	print_info "Installing dependencies..."
	check_profile_argument $1 install

	${PODMAN_CMD} conan install --build missing --install-folder "${MICROSERVICE_BUILD_DIR}/$1" --profile $1 ${MICROSERVICE_ROOT_DIR}
}

function conan_build() {
	check_profile_argument $1 build
	! [[ -d "${PROJECT_BUILD_DIR}_$1" ]] && conan_install $@

	print_info "Building project..."
	${PODMAN_CMD} conan build --build-folder "${MICROSERVICE_BUILD_DIR}/$1" ${MICROSERVICE_ROOT_DIR}
}

function conan_package() {
	check_profile_argument $1 package
	conan_build $@
	${PODMAN_CMD} conan package --build-folder "${MICROSERVICE_BUILD_DIR}/$1" ${MICROSERVICE_ROOT_DIR}
}

function conan_clean() {
	podman run ${PODMAN_OPT} ${PODMAN_VOLUMES} --workdir ${MICROSERVICE_BUILD_DIR} cpp-server-devel-container \
		make clean
}

function clean_all() {
	rm -rf ${PROJECT_BUILD_DIR}
}

function gen_protos() {
	${PODMAN_CMD} protoc \
		-I protos \
		--grpc_out=${MICROSERVICE_SRC_DIR} \
		--plugin=protoc-gen-grpc=`${PODMAN_CMD} which grpc_cpp_plugin` \
		protos/*

	${PODMAN_CMD} protoc \
		-I protos \
		--cpp_out=${MICROSERVICE_SRC_DIR} \
		protos/*
}

# Check for container and build if necessary.
! podman image exists cpp-server-devel-container:latest && container_build

case ${COMMAND} in
	"build_container") container_build;;
	"interactive") container_interact;;
	"deploy") container_deploy;;
	"prepare") conan_prepare;;
	"install") conan_install $@;;
	"build") conan_build $@;;
	"package") conan_package $@;;
	"clean") conan_clean;;
	"purge") clean_all;;
	"gen_protos") gen_protos;;
esac
