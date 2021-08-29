# CMake version
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Declare project
project(HAIArena)

# Set c++ standard
set(CMAKE_CXX_STANDARD 17)

# Set PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# External Libraries
cmake_policy(SET CMP0063 NEW)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(Libraries/pybind11)

include_directories(Libraries/doctest/doctest)

# Includes
include_directories(Includes)

# Project module
add_subdirectory(Sources/Arena)
add_subdirectory(RandomBot)
add_subdirectory(UnitTest)
add_subdirectory(Extension/pyArena)
