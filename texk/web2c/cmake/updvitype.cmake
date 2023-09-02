
## upDVItype

set(nodist_updvitype_SOURCES
  updvitype.c
  updvitype.h
  )

set(dist_updvitype_SOURCES
  uptexdir/kanji.h
  )

set(updvitype_web_srcs
  dvitype.web
  dvitype.ch
  )

set(updvitype_ch_srcs
  uptexdir/updvitype.ch
  )

set(updvitype_SRCS
  ${nodist_updvitype_SOURCES}
  ${dist_updvitype_SOURCES}
  )

if(WIN32)
  add_library(updvitype SHARED ${updvitype_SRCS})
else()
  add_executable(updvitype ${updvitype_SRCS})
endif()

target_compile_definitions(updvitype
  PRIVATE -DHEX_CHAR_CODE
  )

target_include_directories(updvitype
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )

#target_link_libraries(updvitype libukanji ptexenc kpathsea)
target_link_libraries(updvitype libukanji web2c_libp ptexenc libmd5 zlib web2c_lib kpathsea)

#web2c_convert(updvitype OUTPUT ${updvitype_c_h} DEPENDS updvitype.p ${web2c_texmf} uptexdir/uptex.defines)
#web2c_convert(updvitype OUTPUT ${updvitype_c_h} DEPENDS updvitype.p ${web2c_texmf} uptexdir/uptex.defines)

#web2c_tangleboot(updvitype)
web2c_convert(updvitype
  OUTPUT updvitype.c updvitype.h
  DEPENDS updvitype.p ${web2c_texmf} uptexdir/uptex.defines
  )


web2c_texmf_tangle(updvitype OUTPUT updvitype.p updvitype.pool DEPENDS updvitype.web uptexdir/updvitype.ch)

web2c_tie_m(updvitype.web SOURCES ${updvitype_web_srcs})

# updvitype.ch は作らないはず。
#web2c_tie_c(updvitype.ch SOURCES updvitype.web ${updvitype_web_srcs})

