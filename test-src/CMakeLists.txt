# Test vector3d.hpp
add_executable(test_vector3d test_vector3d.cpp)
target_include_directories(test_vector3d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${CATCH_INCLUDE_DIR}
                ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector3d
        ${MPFR_LIBRARIES})

# Test geometry3d.hpp
add_executable(test_geometry3d test_geometry3d.cpp)
target_include_directories(test_geometry3d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${CATCH_INCLUDE_DIR}
                ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_geometry3d
        ${MPFR_LIBRARIES})

# Test vector4d.hpp
add_executable(test_vector4d test_vector4d.cpp)
target_include_directories(test_vector4d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector4d
        ${MPFR_LIBRARIES})

# Test matrix3x3.hpp
add_executable(test_matrix3x3 test_matrix3x3.cpp)
target_include_directories(test_matrix3x3
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix3x3
        ${MPFR_LIBRARIES})

# Test matrix4x4.hpp
add_executable(test_matrix4x4 test_matrix4x4.cpp)
target_include_directories(test_matrix4x4
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix4x4
        ${MPFR_LIBRARIES})

# Test fabbri.hpp
add_executable(test_fabbri test_fabbri.cpp)
target_include_directories(test_fabbri
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_fabbri
        ${MPFR_LIBRARIES})

# Test regular_grid.hpp
add_executable(test_regular_grid test_regular_grid.cpp)
target_include_directories(test_regular_grid
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_regular_grid
        ${MPFR_LIBRARIES})

# Test sample_plane.hpp
add_executable(test_sample_plane test_sample_plane.cpp)
target_include_directories(test_sample_plane
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR}
        ${RAPIDXML_INCLUDE_DIR})
target_link_libraries(test_sample_plane
        HDF5::HDF5
        ${MPFR_LIBRARIES})

##############################################################################
# Integration test                                                           #
##############################################################################

# Integration test
add_executable(integration_001 integration_001.cpp
        ../include/b_field_calculator.hpp)
target_include_directories(integration_001
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${MPREAL_INCLUDE_DIR}
                ${CATCH_INCLUDE_DIR}
                ${MPREAL_INCLUDE_DIR}
                ${RAPIDXML_INCLUDE_DIR})
MESSAGE("RAPIDXML_INCLUDE_DIR: ${RAPIDXML_INCLUDE_DIR}")
target_link_libraries(integration_001
        HDF5::HDF5
        ${MPFR_LIBRARIES})