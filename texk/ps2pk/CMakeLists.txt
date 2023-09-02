# CMakeLists.txt for ps2pk directory

set(PACKAGE_VERSION "1.8")
set(PACKAGE_BUGREPORT "tex-k@tug.org")

include(cmake/config.cmake)

get_property(KPATHSEA_INCLUDES GLOBAL PROPERTY KPATHSEA_INCLUDES)

include_directories(${KPATHSEA_INCLUDES})

set(mag_SOURCES
  basics.c
  basics.h
  mag.c
  )
set(pfb2pfa_SOURCES
  basics.c
  basics.h
  filenames.c
  filenames.h
  pfb2pfa.c
  )
set(pk2bm_SOURCES
  basics.c
  basics.h
  pk2bm.c
  pkin.c
  pkin.h
  )
set(ps2pk_SOURCES
  Xstuff.h
  arith.c
  arith.h
  basics.c
  basics.h
  blues.h
  bstring.c
  cluts.h
  curves.c
  curves.h
  digit.h
  encoding.c
  ffilest.h
  filenames.c
  filenames.h
  font.h
  fontfcn.c
  fontfcn.h
  fontfile.h
  fontmisc.h
  fonts.h
  fontstruct.h
  fontxlfd.h
  fsmasks.h
  hdigit.h
  hints.c
  hints.h
  lines.c
  lines.h
  objects.c
  objects.h
  paths.c
  paths.h
  pictures.h
  pkout.c
  pkout.h
  ps2pk.c
  psearch.h
  regions.c
  regions.h
  scanfont.c
  spaces.c
  spaces.h
  strokes.h
  t1funcs.c
  t1hdigit.h
  t1info.c
  t1intf.h
  t1io.c
  t1snap.c
  t1stdio.h
  token.c
  token.h
  tokst.h
  type1.c
  types.h
  util.c
  util.h
  )
set(pktest_SOURCES
  basics.c
  basics.h
  pkout.c
  pkout.h
  pktest.c
  )

add_executable(mag ${mag_SOURCES})
add_executable(pfb2pfa ${pfb2pfa_SOURCES})
add_executable(pk2bm ${pk2bm_SOURCES})
add_executable(ps2pk ${ps2pk_SOURCES})
add_executable(pktest ${pktest_SOURCES})

target_compile_definitions(mag
  PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H
  )
target_compile_definitions(pfb2pfa
  PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H
  )
target_compile_definitions(pk2bm
  PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H
  )
target_compile_definitions(ps2pk
  PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H
  )
target_compile_definitions(pktest
  PRIVATE -DUNIX -DKPATHSEA -DHAVE_CONFIG_H
  )

target_include_directories(mag
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )
target_include_directories(pfb2pfa
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )
target_include_directories(pk2bm
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )
target_include_directories(ps2pk
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )
target_include_directories(pktest
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )

target_link_libraries(mag kpathsea)
target_link_libraries(pfb2pfa kpathsea)
target_link_libraries(pk2bm kpathsea)
target_link_libraries(ps2pk kpathsea)
target_link_libraries(pktest kpathsea)
