add_library(tetgen STATIC
  ${TETGEN_SRC_DIR}/tetgen.cxx
  ${TETGEN_SRC_DIR}/predicates.cxx
)

target_include_directories(tetgen
  PUBLIC
   ${TETGEN_INCLUDE_DIR}
)