cmake_minimum_required(VERSION 3.22)
project(amiga)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(AMIGA_INCLUDE_DIR      "${CMAKE_SOURCE_DIR}/include")
set(AMIGA_SRC_DIR          "${CMAKE_SOURCE_DIR}/src")
set(AMIGA_THIRD_PARTY_DIR  "${CMAKE_SOURCE_DIR}/third-party")
set(AMIGA_TEST_SRC_DIR     "${CMAKE_SOURCE_DIR}/test-src")
set(AMIGA_TEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR/test-include}")

#----------------------------------------------------------------------------#
# HDF5 library.                                                              #
#----------------------------------------------------------------------------#

find_package(HDF5 COMPONENTS CXX HL REQUIRED)

#----------------------------------------------------------------------------#
# Posix threads.                                                             #
#----------------------------------------------------------------------------#

find_package(Threads REQUIRED)

#----------------------------------------------------------------------------#
# MPFR library.                                                              #
#----------------------------------------------------------------------------#

# Try to load the multiprecision library.
find_package(MPFR REQUIRED)
set(MPREAL_INCLUDE_DIR "${AMIGA_THIRD_PARTY_DIR}/mpreal-v3.7.0/include")

#----------------------------------------------------------------------------#
# Third party libraries.                                                     #
#----------------------------------------------------------------------------#

# Args
set(ARGS_DIR "${AMIGA_THIRD_PARTY_DIR}/args-v6.3.0")
message(STATUS "Args directory: ${ARGS_DIR}")
set(ARGS_INCLUDE_DIR "${ARGS_DIR}/include")
message(STATUS "Args include directory: ${ARGS_INCLUDE_DIR}")

# Catch2
set(CATCH_DIR "${AMIGA_THIRD_PARTY_DIR}/catch2-v2.13.9")
message(STATUS "Catch2 directory: ${CATCH_DIR}")
set(CATCH_INCLUDE_DIR "${CATCH_DIR}/include")
message(STATUS "Catch2 include directory: ${CATCH_INCLUDE_DIR}")

# Eigen
set(EIGEN_DIR "${AMIGA_THIRD_PARTY_DIR}/eigen-v3.4.0")
message(STATUS "Eigen directory: ${EIGEN_DIR}")
set(EIGEN_INCLUDE_DIR "${EIGEN_DIR}/include")
message(STATUS "Eigen include directory: ${EIGEN_INCLUDE_DIR}")

# MPReal
set(MPREAL_DIR "${AMIGA_THIRD_PARTY_DIR}/mpreal-v3.7.0")
message(STATUS "MPReal directory: ${MPREAL_DIR}")
set(MPREAL_INCLUDE_DIR "${MPREAL_DIR}/include")
message(STATUS "MPReal include directory: ${MPREAL_INCLUDE_DIR}")

# RapidXML
set(RAPIDXML_DIR "${AMIGA_THIRD_PARTY_DIR}/rapidxml-v1.13")
message(STATUS "RapidXML directory: ${RAPIDXML_DIR}")
set(RAPIDXML_INCLUDE_DIR "${RAPIDXML_DIR}/include")
message(STATUS "RapidXML include directory: ${RAPIDXML_INCLUDE_DIR}")

# TetGen
set(TETGEN_DIR "${AMIGA_THIRD_PARTY_DIR}/tetgen-v1.6.0")
message(STATUS "TetGen directory: ${TETGEN_DIR}")
set(TETGEN_INCLUDE_DIR "${TETGEN_DIR}/include")
message(STATUS "TetGen include directory: ${TETGEN_INCLUDE_DIR}")
set(TETGEN_SRC_DIR "${TETGEN_DIR}/src")
message(STATUS "TetGen source directory: ${TETGEN_SRC_DIR}")

add_subdirectory(${TETGEN_DIR})

#----------------------------------------------------------------------------#
# Descend in to test directory.                                              #
#----------------------------------------------------------------------------#

enable_testing()
add_subdirectory(${AMIGA_TEST_SRC_DIR})
