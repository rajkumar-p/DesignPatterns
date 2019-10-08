cmake_minimum_required(VERSION 3.14)
project(DesignPatterns)

set(CMAKE_C_COMPILER /usr/local/opt/llvm/bin/clang)
set (CMAKE_CXX_COMPILER /usr/local/opt/llvm/bin/clang++)

set(CMAKE_CXX_STANDARD 17)

# Make debug config the default build type
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type passed, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
endif()

# Compiler options for specific configurations
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")

# Setup include directories
include_directories(include)

add_executable(dp src/main.cpp include/delegate.hpp src/delegate.cpp src/composite.cpp include/composite.hpp
        src/strategy.cpp include/strategy.hpp)

set_target_properties(dp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set_target_properties(dp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)
