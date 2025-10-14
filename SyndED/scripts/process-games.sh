#!/usr/bin/env bash
SCRIPT_DIR="$(dirname -- "$(realpath -- "$0")")"
cd -- "${SCRIPT_DIR}/.." || { echo "Error: failed to change directory" >&2; exit 1; }

# SyndED executables
#SYNDED_DEBUG="build/bin/SyndED_dynamic_debug"
SYNDED_DEBUG="build/bin/SyndED_asandyn_debug"
SYNDED_RELEASE="build/bin/SyndED_dynamic_release"

# Default settings
SYNDED_EXE="${SYNDED_RELEASE}"
VERBOSE_OUTPUT="false"

# Process command line
for arg; do
	case "${arg}" in
		"--debug")   SYNDED_EXE="${SYNDED_DEBUG}"; shift; ;;
		"--verbose") VERBOSE_OUTPUT="true"; shift; ;;
	esac
done

# All games or user-specified games?
if (( $# == 0 )); then
	readarray -t games < <(find games -type f -name 'GAME*.DAT' | sort)
else
	games=("$@")
fi

# Process games
for game in "${games[@]}"; do
	echo "Running SyndED for '${game}'..."
	rm -f -- "${game}_mod"*
	if ${VERBOSE_OUTPUT}; then
		"${SYNDED_EXE}" "${game}" "${game}_mod" |& tee -- "${game}_mod_log.txt"
	else
		"${SYNDED_EXE}" "${game}" "${game}_mod" &> "${game}_mod_log.txt"
	fi
done
