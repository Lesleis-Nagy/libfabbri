# Test vector3d.hpp
add_executable(test_vector3d test_vector3d.cpp)
target_include_directories(test_vector3d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${CATCH_INCLUDE_DIR}
                ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector3d
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

# Test matrix3x3.hpp
add_executable(test_matrix3x3 test_matrix3x3.cpp)
target_include_directories(test_matrix3x3
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix3x3
        ${MPFR_LIBRARIES})
