#!/usr/bin/env bash
SCRIPT_DIR="$(dirname -- "$(realpath -- "$0")")"
cd -- "${SCRIPT_DIR}/.." || { echo "Error: failed to change directory" >&2; exit 1; }

# Compare GAME??.DAT files of Syndicate vs. American Revolt
readarray -t games < <(find games -type f -name 'GAME*.DAT' -printf "%f\n" | sort | uniq)
only=0; differ=0; same=0
for game in "${games[@]}"; do
	echo -n "Comparing '${game}'... "
	synd="games/Synd/${game%.*}/${game}"; amrev="games/AmRev/${game%.*}/${game}"
	[[ -f "${synd}" && ! -f "${amrev}" ]] && { echo -e "\e[1;33monly in Syndicate\e[0m"; only=$((only + 1)); continue; }
	[[ -f "${amrev}" && ! -f "${synd}" ]] && { echo -e "\e[1;33monly in American Revolt\e[0m"; only=$((only + 1)); continue; }
	cmp -s -- "${synd}" "${amrev}" && { echo -e "\e[1;32msame\e[0m"; same=$((same + 1)); } || { echo -e "\e[1;31mdiffer\e[0m"; differ=$((differ + 1)); }
done
echo
echo "Only in: ${only}"
echo "Same:    ${same}"
echo "Differ:  ${differ}"
