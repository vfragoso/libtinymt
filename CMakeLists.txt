# Porting TinyMT an efficient MersenneTwister PRNG.
# This code is heavily inspired on https://github.com/MersenneTwister-Lab/TinyMT.

cmake_minimum_required(VERSION 3.1)
project(tinymt C CXX)

# Include dirs.
set(LIBTINYMT_INCLUDE_DIRS src/)
include_directories(${LIBTINYMT_INCLUDE_DIRS})

# Src. files.
set(LIBTINYMT_SRC src/libtinymt/tinymt.cc)

# Compile gdls* library.
add_library(tinymt STATIC ${LIBTINYMT_SRC})
target_link_libraries(tinymt)
