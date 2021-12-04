function conan_check_profile_argument {
	if [[ -z "$1" ]];
	then
		print_err "Profile must be provided in command"
		print_norm "Available Profiles:"
		echo -e " + ${MAGENTA}development${NORM}"
		echo -e " + ${MAGENTA}production${NORM}\n"
		print_info "Usage: ./run.sh $2 <profile>"
		return 1
	else
		return 0
	fi
}

function conan_create_profile {
	! [ -f "${PROJECT_ROOT_DIR}/.conan/profiles/$1" ] && (
		${PODMAN_CMD} \
			conan profile new $1 && \
			conan profile update settings.os=Linux $1 && \
			conan profile update settings.os_build=Linux $1 && \
			conan profile update settings.arch=x86_64 $1 && \
			conan profile update settings.arch_build=x86_64 $1 && \
			conan profile update settings.build_type=$2 $1 && \
			conan profile update settings.compiler=clang $1 && \
			conan profile update settings.compiler.cppstd=17 $1 && \
			conan profile update settings.compiler.version=12 $1 && \
			conan profile update settings.compiler.libcxx=libstdc++11 $1 && \
			conan profile update env.CC=/usr/bin/clang $1 && \
			conan profile update env.CXX=/usr/bin/clang++ $1 && \
			conan profile update env.CONAN_CPU_COUNT=6 $1
	)
}

function conan_prepare {
	conan_create_profile default Debug
	conan_create_profile development Debug
	conan_create_profile production Release
}

function conan_fetch {
	conan_prepare
	conan_check_profile_argument "$1" fetch && (
		print_info "Fetching dependencies..."
		${PODMAN_RUN_DEVEL} \
			conan install \
				--build missing \
				--install-folder "${MICROSERVICE_BUILD_DIR}/$1" \
				--profile "$1" \
				${MICROSERVICE_ROOT_DIR}
	)
}

function conan_build {
	conan_check_profile_argument "$1" build && (
		! [[ -d "${PROJECT_BUILD_DIR}/$1" ]] && conan_install $@

		print_info "Building project..."
		${PODMAN_RUN_DEVEL} \
			conan build \
				--build-folder "${MICROSERVICE_BUILD_DIR}/$1" \
				${MICROSERVICE_ROOT_DIR}
	)
}

function conan_package {
	conan_check_profile_argument "$1" pack && (
		conan_build $@

		print_info "Packaging project..."
		${PODMAN_RUN_DEVEL} \
			conan package \
				--build-folder "${MICROSERVICE_BUILD_DIR}/$1" \
				${MICROSERVICE_ROOT_DIR}
	)
}

function conan_clean_build {
	conan_check_profile_argument "$1" clean && (
		${PODMAN_RUN_DEVEL} make -C "${MICROSERVICE_BUILD_DIR}/$1" clean
	)
}

function conan_purge_build {
	conan_check_profile_argument "$1" purge && (
		rm -rf "${PROJECT_BUILD_DIR}/$1"
	)
}

function conan_reset {
	conan_purge_build development
	conan_purge_build production
	rm -rf ${PROJECT_ROOT_DIR}/.conan
}