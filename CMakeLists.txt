cmake_minimum_required(VERSION 3.13)
project(basicini)

option(ENABLE_TEST "Build the test executable" OFF)

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# C++ Standard
if (NOT MSVC)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_subdirectory(src)
