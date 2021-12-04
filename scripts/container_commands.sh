function build_container {
	print_info "Building devel container..."
	${PODMAN_BUILD_DEVEL}
}

function deploy_container {
	print_info "Building prod container..."
	${PODMAN_BUILD_PROD}
}

function interact_container {
	print_info "Opening container in interactive mode..."
	print_info "Mounting ${PODMAN_VOLUME}"
	${PODMAN_RUN_INTERACT} $@
}

function clean_container {
	if [[ "$1" == "--devel" ]];
	then
		${PODMAN_CLEAN_DEVEL}
	elif [[ "$1" == "--prod" ]];
	then
		${PODMAN_CLEAN_PROD}
	fi

	${PODMAN_PRUNE_IMAGES}
}
