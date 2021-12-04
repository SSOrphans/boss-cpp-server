function print_norm {
	echo -e "${NORM}-- $1"
}

function print_info {
	echo -e "${CYAN}-- $1${NORM}"
}

function print_warn {
	echo -e "${YELLOW}-- $1${NORM}"
}

function print_err {
	echo -e "${RED}-- $1${NORM}"
}

function error {
	>&2 print_error $@
	exit 1
}
