# Test vector2d.hpp
add_executable(test_vector2d test_vector2d.cpp)
target_include_directories(test_vector2d
        PUBLIC ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector2d
        ${MPFR_LIBRARIES})
add_test(NAME test_vector2d COMMAND test_vector2d)

# Test vector3d.hpp
add_executable(test_vector3d test_vector3d.cpp)
target_include_directories(test_vector3d
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector3d
        ${MPFR_LIBRARIES})
add_test(NAME test_vector3d COMMAND test_vector3d)

# Test vector4d.hpp
add_executable(test_vector4d test_vector4d.cpp)
target_include_directories(test_vector4d
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_vector4d
        ${MPFR_LIBRARIES})
add_test(NAME test_vector4d COMMAND test_vector4d)

# Test geometry.hpp
add_executable(test_geometry test_geometry.cpp)
target_include_directories(test_geometry
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_geometry
        ${MPFR_LIBRARIES})
add_test(NAME test_geometry COMMAND test_geometry)

# Test matrix2x2.hpp
add_executable(test_matrix2x2 test_matrix2x2.cpp)
target_include_directories(test_matrix2x2
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix2x2
        ${MPFR_LIBRARIES})
add_test(NAME test_matrix2x2 COMMAND test_matrix2x2)

# Test matrix3x3.hpp
add_executable(test_matrix3x3 test_matrix3x3.cpp)
target_include_directories(test_matrix3x3
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix3x3
        ${MPFR_LIBRARIES})
add_test(NAME test_matrix3x3 COMMAND test_matrix3x3)

# Test matrix4x4.hpp
add_executable(test_matrix4x4 test_matrix4x4.cpp)
target_include_directories(test_matrix4x4
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix4x4
        ${MPFR_LIBRARIES})
add_test(NAME test_matrix4x4 COMMAND test_matrix4x4)

# Test matrix.hpp
add_executable(test_matrix test_matrix.cpp)
target_include_directories(test_matrix
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_matrix
        ${MPFR_LIBRARIES})
add_test(NAME test_matrix COMMAND test_matrix)

# Test fabbri.hpp
add_executable(test_fabbri test_fabbri.cpp)
target_include_directories(test_fabbri
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_fabbri
        ${MPFR_LIBRARIES})
add_test(NAME test_fabbri COMMAND test_fabbri)

# Test octree.hpp
add_executable(test_octree test_octree.cpp)
target_include_directories(test_octree
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_octree
        ${MPFR_LIBRARIES})
add_test(NAME test_octree COMMAND test_octree)

# Test tetrahedron.hpp
add_executable(test_tetrahedron test_tetrahedron.cpp)
target_include_directories(test_tetrahedron
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_tetrahedron
        ${MPFR_LIBRARIES})
add_test(NAME test_tetrahedron COMMAND test_tetrahedron)

# Test box.hpp
add_executable(test_box test_box.cpp)
target_include_directories(test_box
        PRIVATE ${AMIGA_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_box
        ${MPFR_LIBRARIES})
add_test(NAME test_box COMMAND test_box)
