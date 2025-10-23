#!/usr/bin/env bash
SCRIPT_DIR="$(dirname -- "$(realpath -- "$0")")"
cd -- "${SCRIPT_DIR}/.." || { echo "Error: failed to change directory" >&2; exit 1; }

#START_OFFSET=0x1cf898  # start of game data within memory dump
#DATA_LENGTH=0x1c52a    # length of game data
START_OFFSET=1898648    # same as above, converted to decimal for dd
DATA_LENGTH=116010      # same as above, converted to decimal for dd

if (( $# != 2 )); then
	echo "Usage: ${0##*/} infile.bin outfile.dat"
	exit 2
fi

# https://stackoverflow.com/a/40792605
dd if="$1" of="$2" skip=${START_OFFSET} count=${DATA_LENGTH} iflag=skip_bytes,count_bytes
