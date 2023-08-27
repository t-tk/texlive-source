# CMakeLists.txt for detex directory

set(VERSION "2.8.91")

include(cmake/config.cmake)

get_property(KPATHSEA_INCLUDES GLOBAL PROPERTY KPATHSEA_INCLUDES)

include_directories(${KPATHSEA_INCLUDES})

set(SRC detex-src)

set(detex_SOURCES
  ${SRC}/detex.c
  ${SRC}/detex.h
  )

add_executable(detex ${detex_SOURCES})

target_include_directories(detex
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  PUBLIC "${KPATHSEA_INCLUDES}"
  )

target_compile_definitions(detex PRIVATE -DNO_MALLOC_DECL -DKPATHSEA -Dlint -DYY_NO_UNISTD_H)

target_link_libraries(detex kpathsea)
