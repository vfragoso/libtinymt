# Porting TinyMT an efficient MersenneTwister PRNG.
# This code is heavily inspired on https://github.com/MersenneTwister-Lab/TinyMT.

cmake_minimum_required(VERSION 3.1)
project(tinymt C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
option(BUILD_TESTING "Enable testing" OFF)

# Include dirs.
set(LIBTINYMT_INCLUDE_DIRS src/)
include_directories(${LIBTINYMT_INCLUDE_DIRS})

# Src. files.
set(LIBTINYMT_SRC src/tinymt/tinymt.cc)

# Compile tinymt library.
add_library(tinymt STATIC ${LIBTINYMT_SRC})
target_link_libraries(tinymt)

# Enable unit tests.
# Find gtest for building unit tests.
if (BUILD_TESTING)
  enable_testing()
  # Download and unpack googletest at configure time.
  # Snippet of code from:
  # https://github.com/google/googletest/blob/master/googletest/README.md
  configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/GoogleTest.CmakeLists.txt.in
    googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL)

  # Compile Unit tests.
  add_executable(tinymt_test test/test_main.cc src/tinymt/tinymt_test.cc)
  # Link binary.
  target_link_libraries(tinymt_test gtest tinymt)
endif()

