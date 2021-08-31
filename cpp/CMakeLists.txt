# CMake version
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Declare project
project(HAIArena)

# Set c++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Libraries/pybind11)

include_directories(Libraries/doctest/doctest)

# Includes
include_directories(Includes)

# Project module
add_subdirectory(Sources/Arena)
add_subdirectory(RandomBot)
add_subdirectory(UnitTest)
add_subdirectory(Extension/pyArena)
