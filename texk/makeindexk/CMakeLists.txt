# CMakeLists.txt for makeindexk directory

include(cmake/config.cmake)

get_property(KPATHSEA_INCLUDES GLOBAL PROPERTY KPATHSEA_INCLUDES)

include_directories(${KPATHSEA_INCLUDES})

set(makeindex_SOURCES
  genind.c
  genind.h
  mkind.c
  mkind.h
  qsort.c
  qsort.h
  scanid.c
  scanid.h
  scanst.c
  scanst.h
  sortid.c
  )

add_executable(makeindex ${makeindex_SOURCES})

target_compile_definitions(makeindex PUBLIC -DKPATHSEA -DUNIX)
target_include_directories(makeindex
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )

target_link_libraries(makeindex kpathsea)
