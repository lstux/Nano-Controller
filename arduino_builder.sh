#!/bin/sh
SCRIPTFILE="$(realpath "${0}")"
SKETCHDIR="$(dirname "${SCRIPTFILE}")"
SKETCHNAME="$(basename "${SKETCHDIR}")"
SKETCHFILE="${SKETCHDIR}/${SKETCHNAME}.ino"
SKETCHBOOK_PATH="${SKETCHBOOK_PATH:-}"
#BUILD_PATH="${BUILD_PATH:-${SKETCHDIR}/build}"
BUILD_PATH="${BUILD_PATH:-/tmp/arduino/${SKETCHNAME}}"

#ARDUINO_BOARD="arduino:avr:nano:cpu=atmega328old"
ARDUINO_BOARD="arduino:avr:nano"
UPLOAD_PORT="${UPLOAD_PORT:-/dev/ttyUSB0}"

if ! [ -d "${SKETCHBOOK_PATH}" ]; then
  PREFERENCES="${HOME}/.arduino15/preferences.txt"
  if [ -e "${PREFERENCES}" ]; then
   SKETCHBOOK_PATH="$(sed -n 's/^sketchbook.path=//p' "${PREFERENCES}")"
   printf "sketchbook.path is '${SKETCHBOOK_PATH}'\n"
  else
    printf "Error : can't define sketchbook.path, set it in '${PREFERENCES}' or export SKETCHBOOK_PATH environement variable\n"
    exit 1
  fi
fi

usage() {
  exec >&2
  printf "Usage : $(basename "${0}") {verify|upload|all|clean|libraries}\n"
  exit 1
}

verify() {
  arduino --verify --verbose --board "${ARDUINO_BOARD}" --pref build.path="${BUILD_PATH}" --pref sketchbook.path="${SKETCHBOOK_PATH}" "${SKETCHFILE}"
}

upload() {
  arduino --upload --verbose --board "${ARDUINO_BOARD}" --port "${UPLOAD_PORT}" --pref build.path="${BUILD_PATH}" --pref sketchbook.path="${SKETCHBOOK_PATH}" "${SKETCHFILE}"
}

libraries() {
  [ -e "${SKETCHDIR}/libraries.txt" ] || { printf "Error : can't find '${SKETCHDIR}/libraries.txt'..." >&2; exit 2; }
  local libdir="${SKETCHBOOK_PATH}/libraries"
  egrep -v "^#" "${SKETCHDIR}/libraries.txt" | while read libname link commands; do
    case "${libname}" in
      ""|"#"*) continue;;
    esac
    printf "\n\n"
    case "${link}" in
      "")    printf "Installing library '${libname}' through arduino\n"
             arduino --install-library "${libname}";;
      *.git) printf "Installing library '${libname}' with git (${link})\n"
             if [ -d "${libdir}/$(basename "${link}" .git)" ]; then
               cd "${libdir}/$(basename "${link}" .git)" && git pull
             else
               cd "${libdir}" && git clone "${link}"
             fi
             [ $? -eq 0 ] || continue;;
      *)     printf "Unsupported link format for '${libname}' (${link})\n" >&2; continue;;
    esac
    if [ -n "${commands}" ]; then eval "${commands}"; fi
  done
}

case "${1}" in
  verify)    verify;;
  upload)    upload;;
  clean)     rm -rf "${BUILD_PATH}";;
  all)       verify && upload;;
  libraries) libraries;;
  *)         usage;;
esac
