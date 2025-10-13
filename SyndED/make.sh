#!/usr/bin/env bash
SCRIPT_DIR="$(dirname -- "$(realpath -- "$0")")"
cd -- "${SCRIPT_DIR}" || exit 1
gcc -o synded synded.c csvoutput.c mapwho.c asprintf.c -Wall -Wextra "$@"
