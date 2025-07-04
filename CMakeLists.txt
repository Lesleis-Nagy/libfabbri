cmake_minimum_required(VERSION 3.22)
project(libfabbri)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(LIBFABBRI_INCLUDE_DIR      "${CMAKE_SOURCE_DIR}/include")
set(LIBFABBRI_SRC_DIR          "${CMAKE_SOURCE_DIR}/src")
set(LIBFABBRI_THIRD_PARTY_DIR  "${CMAKE_SOURCE_DIR}/third-party")
set(LIBFABBRI_TEST_SRC_DIR     "${CMAKE_SOURCE_DIR}/test-src")
set(LIBFABBRI_TEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR/test-include}")

#----------------------------------------------------------------------------#
# HDF5 library.                                                              #
#----------------------------------------------------------------------------#

find_package(HDF5 COMPONENTS CXX HL REQUIRED)

#----------------------------------------------------------------------------#
# VTK library.                                                               #
#----------------------------------------------------------------------------#

find_package (VTK REQUIRED)

#----------------------------------------------------------------------------#
# Posix threads.                                                             #
#----------------------------------------------------------------------------#

find_package(Threads REQUIRED)

#----------------------------------------------------------------------------#
# MPFR library.                                                              #
#----------------------------------------------------------------------------#

# Try to load the multiprecision library.
find_package(MPFR REQUIRED)
set(MPREAL_INCLUDE_DIR "${LIBFABBRI_THIRD_PARTY_DIR}/mpreal-v3.7.0/include")

#----------------------------------------------------------------------------#
# Third party libraries.                                                     #
#----------------------------------------------------------------------------#

# Catch
set(CATCH_INCLUDE_DIR "${LIBFABBRI_THIRD_PARTY_DIR}/catch2-v2.13.9/include")

# RapidXML
set(RAPIDXML_INCLUDE_DIR "${LIBFABBRI_THIRD_PARTY_DIR}/rapidxml-v1.13/include")

#----------------------------------------------------------------------------#
# Descend in to test directory.                                              #
#----------------------------------------------------------------------------#

add_subdirectory(${LIBFABBRI_TEST_SRC_DIR})
