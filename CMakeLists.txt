cmake_minimum_required(VERSION 3.22)
project(libfabbri)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_INCLUDE_DIR    "${CMAKE_SOURCE_DIR}/include")
set(PROJECT_SRC_DIR        "${CMAKE_SOURCE_DIR}/src")
set(PROJECT_THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")

if (${MULTIPRECISION})
    message(STATUS "Building a multiprecision version of libfabbri.")

    # Try to load the multiprecision library.
    find_package(MPFR REQUIRED)

    # Print some messages.
    message(STATUS "Found MPFR, details follow ...")
    message(STATUS "MPFR_INCLUDES:  ${MPFR_INCLUDES}")
    message(STATUS "MPFR_LIBRARIES: ${MPFR_LIBRARIES}")
    message(STATUS "MPFR_VERSION:   ${MPFR_VERSION}")

    # Add mpreal.
    set(MPREAL_INCLUDE_DIR "${PROJECT_THIRDPARTY_DIR}/mpreal-v4.2.0/include")
    message(STATUS "MPREAL_INCLUDE_DIR: ${MPREAL_INCLUDE_DIR}")

endif()

if (${BUILD_TESTS})

    message(STATUS "Building tests.")

    set(PROJECT_TEST_SRC_DIR     "${CMAKE_SOURCE_DIR}/test-src")
    set(PROJECT_TEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR/test-include}")
    set(CATCH_INCLUDE_DIR        "${PROJECT_THIRDPARTY_DIR}/catch2-v2.13.9/include")

    add_subdirectory(${PROJECT_TEST_SRC_DIR})

endif()
