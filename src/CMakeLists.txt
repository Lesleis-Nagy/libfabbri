# mvpusc - executable
add_executable(mvpusc mvpusc.cpp ../third-party/rapidxml-v1.13/include/rapidxml_ext.hpp)
target_include_directories(mvpusc
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${MPREAL_INCLUDE_DIR}
                ${ARGS_INCLUDE_DIR}
                ${RAPIDXML_INClUDE_DIR}
                ${HDF5_INCLUDE_DIR})
target_link_libraries(mvpusc
        ${CURSES_LIBRARIES}
        ${MPFR_LIBRARIES}
        ${HDF5_LIBRARIES}
        ${HDF5_CXX_LIBRARIES})