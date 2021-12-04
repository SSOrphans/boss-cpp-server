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

function display_commands {
	print_norm "Available Commands:"
	echo -e " + ${MAGENTA}interactive${NORM} - Opens development container in interactive mode"
	echo -e " + ${MAGENTA}fetch${NORM}       - Fetches Conan dependencies and builds them"
	echo -e " + ${MAGENTA}build${NORM}       - Builds the server application"
	echo -e " + ${MAGENTA}pack${NORM}        - Packages the server application"
	echo -e " + ${MAGENTA}clean${NORM}       - Cleans the server application build using 'make clean'"
	echo -e " + ${MAGENTA}purge${NORM}       - Erases the server application build"
	echo -e " + ${MAGENTA}reset${NORM}       - Erases the Conan cache and builds"
	echo -e " + ${MAGENTA}local${NORM}       - Runs the application locally"
	echo -e " + ${MAGENTA}server${NORM}      - Runs the application in its production environment\n"
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
	"generate_protos") generate_protos;;

	# Common commands.
	"help") display_commands;;
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
