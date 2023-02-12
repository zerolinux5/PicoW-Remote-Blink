# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)
#include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico-spi C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)
# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()
# Add subdirectories for the separate executables.
add_subdirectory(controller)
add_subdirectory(peripheral)