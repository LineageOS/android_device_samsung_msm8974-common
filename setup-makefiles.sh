#!/bin/bash
#
# Copyright (C) 2017-2021 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

set -e

if [ -z "${BOARD_COMMON}" ]; then
    echo ""
    echo "error: This is a script in a common tree. Please execute" $(basename $0) "from a device tree."
    echo ""
    exit 1
fi

# Override anything that may come from the calling environment
BOARD=msm8974
DEVICE_COMMON="${BOARD_COMMON}"

# Load extract_utils and do some sanity checks
MY_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "${MY_DIR}" ]]; then MY_DIR="${PWD}"; fi

ANDROID_ROOT="${MY_DIR}/../../.."

HELPER="${ANDROID_ROOT}/tools/extract-utils/extract_utils.sh"
if [ ! -f "${HELPER}" ]; then
    echo "Unable to find helper script at ${HELPER}"
    exit 1
fi
source "${HELPER}"

# Initialize the helper for common
setup_vendor "${BOARD_COMMON}" "${VENDOR}" "${ANDROID_ROOT}" true

# Warning headers and guards
write_headers "${BOARD}" "TARGET_BOARD_PLATFORM"

# The standard common blobs
write_makefiles "${MY_DIR}/common-proprietary-files.txt" true

# Finish
write_footers
