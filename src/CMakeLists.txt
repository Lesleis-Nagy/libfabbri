add_executable(mvpusc mvpusc.cpp ../include/table.hpp)
target_include_directories(mvpusc
        PRIVATE ${LIBFABBRI_INCLUDE_DIR}
                ${MPFR_INCLUDES}
                ${MPREAL_INCLUDE_DIR}
                ${ARGS_INCLUDE_DIR})
target_link_libraries(mvpusc
        ${CURSES_LIBRARIES}
        ${MPFR_LIBRARIES})