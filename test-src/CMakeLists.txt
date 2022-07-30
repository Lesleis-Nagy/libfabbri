# Test vector3d.hpp
add_executable(test_vector3d test_vector3d.cpp)
target_include_directories(test_vector3d
        PRIVATE ${PROJECT_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${CATCH_INCLUDE_DIR}
                ${MPREAL_INCLUDE_DIR})

target_link_libraries(test_vector3d
        ${MPFR_LIBRARIES})

# Test fabbri.hpp
add_executable(test_fabbri test_fabbri.cpp)
target_include_directories(test_fabbri
        PRIVATE ${PROJECT_INCLUDE_DIR}
        ${MPFR_INCLUDES}
        ${CATCH_INCLUDE_DIR}
        ${MPREAL_INCLUDE_DIR})
target_link_libraries(test_fabbri
        ${MPFR_LIBRARIES})
