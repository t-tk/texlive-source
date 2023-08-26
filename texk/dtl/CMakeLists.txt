# CMakeLists.txt for dviout-util directory

set(VERSION "0.6.0")
set(PACKAGE_BUGREPORT "tex-k@tug.org")

#cmake_policy (SET CMP0115 NEW)

include(cmake/config.cmake)

get_property(KPATHSEA_INCLUDES GLOBAL PROPERTY KPATHSEA_INCLUDES)

include_directories(${KPATHSEA_INCLUDES})

set(dt2dv_SOURCES
  dt2dv.c dtl.h
  )
set(dv2dt_SOURCES
  dv2dt.c dtl.h
  )

add_executable(dt2dv ${dt2dv_SOURCES})
add_executable(dv2dt ${dv2dt_SOURCES})

target_include_directories(dt2dv
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  PUBLIC "${KPATHSEA_INCLUDES}"
  )
target_include_directories(dv2dt
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  PUBLIC "${KPATHSEA_INCLUDES}"
  )

target_compile_definitions(dt2dv PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H)
target_compile_definitions(dv2dt PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H)

target_link_libraries(dt2dv kpathsea)
target_link_libraries(dv2dt kpathsea)
