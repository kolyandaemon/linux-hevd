#
# HEVD CMake Script
#
cmake_minimum_required(VERSION 3.8)

project("HEVD" C)

set(HEVD_VERSION "3.0")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

message("Detecting OS and Architecture")
include(DetectOS)

# validate supported OS
if(HOST_OS_LINUX)
    message(STATUS "OS: Linux")
else()
    message(FATAL_ERROR "Unsupported OS")
    return()
endif()

if(HOST_ARCH_X64)
    message(STATUS "Architecture: x64")
elseif(HOST_ARCH_X86)
    message(STATUS "Architecture: x86")
else()
    message(FATAL_ERROR "Unsupported architecture")
    return()
endif()

if(HOST_OS_LINUX)
    message("Locating Linux Kernel Module Builder")
    include(LKM)
endif()

add_subdirectory("HEVD")
