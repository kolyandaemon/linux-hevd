#!/usr/bin/env bash


echo "${BANNER}"

# Standard constants
BUILD_ARCH=x64
CURRENT_DIR=$PWD
PROJECT_NAME=hevd
PROJECT_DIR="$(realpath -m ${CURRENT_DIR}/../sources)"
BUILD_DIR="$(realpath -m ${PROJECT_DIR}/../_output)"
BINARY_DIR="$(realpath -m ${PROJECT_DIR}/../output/linux/vulnerable/${BUILD_ARCH})"

echo "[+] Build target architecture: ${BUILD_ARCH}"
echo "[+] Host Architecture: $(uname -m)"
echo "[+] Build directory: ${BUILD_DIR}"
echo "[+] Binary directory: ${BINARY_DIR}"
echo "[+] Removing build & binary directory"

if [ -d "${BUILD_DIR}" ]; then
	rm -rfd ${BUILD_DIR}
fi

if [ -d "${BINARY_DIR}" ]; then
	rm -rfd ${BINARY_DIR}
fi

echo "[+] Creating build directory"

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

echo "[+] Generating build configuration files"

$(which cmake) -G "Unix Makefiles" "${PROJECT_DIR}"

echo
echo "[+] Building vulnerable HackSys Extreme Vulnerable Driver"
echo

$(which make)
echo

echo "[+] Creating binary directory"
mkdir -p ${BINARY_DIR}

echo "[+] Copying built files"

echo "[*] ${PROJECT_NAME}.ko"
mv -f "${BUILD_DIR}/${PROJECT_NAME}.ko" "${BINARY_DIR}"
echo

echo "[+] Cleaning build directory"

$(which make) clean
rm -rf ${BUILD_DIR}

echo "[+] Built vulnerable HackSys Extreme Vulnerable Driver successfully"
echo
