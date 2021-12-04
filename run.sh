#!/bin/bash
source $(dirname "$0")/scripts/variables.sh
source $(dirname "$0")/scripts/print_functions.sh
source $(dirname "$0")/scripts/container_commands.sh
source $(dirname "$0")/scripts/conan_commands.sh

function run_local_application {
	${PROJECT_BUILD_DIR}/$1/package/bin/cppserver
}

function run_server_application {
	${PODMAN_RUN_PROD} ${MICROSERVICE_ROOT_DIR}/cppserver
}

COMMAND=$1
shift

# Check for build container.
! podman image exists cpp-server-devel:latest && build_container

# Process local command into script function.
case ${COMMAND} in
	# Incase you need to do this manually.
	"build_container") build_container;;
	"clean_container") clean_container;;
	"conan_prepare") conan_prepare;;

	# Common commands.
	"interactive") interact_container;;
	"fetch") conan_fetch $@;;
	"build") conan_build $@;;
	"pack") conan_package $@;;
	"clean") conan_clean_build $@;;
	"purge") conan_purge_build $@;;
	"reset") conan_reset;;
	"local") run_local_application $@;;
	"server") run_server_application $@;;
esac
