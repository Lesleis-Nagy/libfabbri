cmake_minimum_required(VERSION 3.22)
project(libfabbri)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(LIBFABBRI_INCLUDE_DIR     "${CMAKE_SOURCE_DIR}/include")
set(LIBFABBRI_SRC_DIR         "${CMAKE_SOURCE_DIR}/src")
set(LIBFABBRI_THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/third-party")

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
    set(MPREAL_INCLUDE_DIR "${LIBFABBRI_THIRD_PARTY_DIR}/mpreal-v3.7.0/include")
    message(STATUS "MPREAL_INCLUDE_DIR: ${MPREAL_INCLUDE_DIR}")

endif()

if (${BUILD_TESTS})

    message(STATUS "Building tests.")

    if (TEST_DEBUG_MESSAGES)
        message(STATUS "Building tests with test messages")
        add_compile_definitions(TEST_DEBUG_MESSAGES=1)
    endif()

    set(LIBFABBRI_TEST_SRC_DIR     "${CMAKE_SOURCE_DIR}/test-src")
    set(LIBFABBRI_TEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR/test-include}")
    set(CATCH_INCLUDE_DIR          "${LIBFABBRI_THIRD_PARTY_DIR}/catch2-v2.13.9/include")

    add_subdirectory(${LIBFABBRI_TEST_SRC_DIR})

endif()

if (${BUILD_UTILS})

    message(STATUS "Building utilities.")

    find_package(HDF5 COMPONENTS CXX REQUIRED)
    find_package(Curses REQUIRED)

    message(STATUS "HDF5_INCLUDE_DIR    ${HDF5_INCLUDE_DIR}")
    message(STATUS "HDF5_LIBRARIES:     ${HDF5_LIBRARIES}")
    message(STATUS "HDF5_CXX_LIBRARIES: ${HDF5_CXX_LIBRARIES}")

    set(ARGS_INCLUDE_DIR     "${LIBFABBRI_THIRD_PARTY_DIR}/args-v6.3.0/include")
    message(STATUS "ARGS_INCLUDE_DIR:     ${ARGS_INCLUDE_DIR}")

    set(RAPIDXML_INClUDE_DIR "${LIBFABBRI_THIRD_PARTY_DIR}/rapidxml-v1.13/include")
    message(STATUS "RAPIDXML_INClUDE_DIR: ${RAPIDXML_INClUDE_DIR}")

    add_subdirectory(${LIBFABBRI_SRC_DIR})

endif()
