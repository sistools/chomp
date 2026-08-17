#! /bin/bash

#############################################################################
# File:     generate_doxygen.sh
#
# Purpose:  Generates HTML API documentation from public headers via Doxygen
#
#############################################################################

ScriptPath=$0
Dir=$(cd "$(dirname "$ScriptPath")" && pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}

if [[ $# -gt 0 ]]; then
  case $1 in
    --help)
      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      printf 'Generates HTML API documentation from public headers via Doxygen\n\n'
      printf '%s [--help]\n' "$ScriptPath"
      exit 0
      ;;
    *)
      >&2 printf '%s: unrecognised argument %s; use --help for usage\n' "$ScriptPath" "$1"
      exit 1
      ;;
  esac
fi

cd "$Dir" || exit 1

if ! command -v doxygen >/dev/null 2>&1; then
  >&2 printf '%s: doxygen not found on PATH\n' "$ScriptPath"
  exit 1
fi

mkdir -p "${CMakeDir}/doxygen"

{
  cat Doxyfile
  printf '\n# Output directory (overridden by %s)\n' "$Basename"
  printf 'OUTPUT_DIRECTORY = %s/doxygen\n' "$CMakeDir"
} | doxygen -

printf 'API documentation written to %s/doxygen/html/index.html\n' "$CMakeDir"
