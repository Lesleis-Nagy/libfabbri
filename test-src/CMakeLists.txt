
# Test vector3d.hpp
add_executable(test_vector3d test_vector3d.cpp)
target_include_directories(test_vector3d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${CATCH_INCLUDE_DIR}
                ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector3d
        ${MPFR_LIBRARIES})
add_test(NAME test_vector3d COMMAND test_vector3d)

# Test vector4d.hpp
add_executable(test_vector4d test_vector4d.cpp)
target_include_directories(test_vector4d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector4d
        ${MPFR_LIBRARIES})
add_test(NAME test_vector4d COMMAND test_vector4d)

# Test geometry3d.hpp
add_executable(test_geometry3d test_geometry3d.cpp)
target_include_directories(test_geometry3d
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_geometry3d
        ${MPFR_LIBRARIES})
add_test(NAME test_geometry3d COMMAND test_geometry3d)

# Test matrix3x3.hpp
add_executable(test_matrix3x3 test_matrix3x3.cpp)
target_include_directories(test_matrix3x3
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix3x3
        ${MPFR_LIBRARIES})
add_test(NAME test_matrix3x3 COMMAND test_matrix3x3)

# Test matrix4x4.hpp
add_executable(test_matrix4x4 test_matrix4x4.cpp)
target_include_directories(test_matrix4x4
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix4x4
        ${MPFR_LIBRARIES})
add_test(NAME test_matrix4x4 COMMAND test_matrix4x4)

# Test fabbri.hpp
add_executable(test_fabbri test_fabbri.cpp)
target_include_directories(test_fabbri
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_fabbri
        ${MPFR_LIBRARIES})
add_test(NAME test_fabbri COMMAND test_fabbri)
