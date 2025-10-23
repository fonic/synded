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
	readarray -t games < <(find games -type f -name '*.DAT_in' | sort)
else
	games=("$@")
fi

# Process games
for game in "${games[@]}"; do
	if ${VERBOSE_OUTPUT}; then
		echo -e "\e[1mRunning SyndED for '${game}':\e[0m"; echo
		rm -f -- "${game}"_*
		"${SYNDED_EXE}" "${game}" "${game%_*}_out" |& tee -- "${game%_*}_out_zlog.txt"
	else
		echo -n "Running SyndED for '${game}'... "
		rm -f -- "${game}"_*
		"${SYNDED_EXE}" "${game}" "${game%_*}_out" &> "${game%_*}_out_zlog.txt"
		(( $? == 0 )) && echo -e "\e[1;32msuccess\e[0m" || echo -e "\e[1;31mfailed\e[0m"
	fi
done
