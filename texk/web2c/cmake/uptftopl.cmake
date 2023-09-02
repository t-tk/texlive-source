
## upTFtoPL

set(nodist_uptftopl_SOURCES
  uptftopl.c
  uptftopl.h
  )

set(dist_uptftopl_SOURCES
  uptexdir/kanji.h
  )

set(uptftopl_web_srcs
  tftopl.web
  tftopl.ch
  )

set(uptftopl_ch_srcs
  uptexdir/uptftopl.ch
  )

set(uptftopl_SRCS
  ${nodist_uptftopl_SOURCES}
  ${dist_uptftopl_SOURCES}
  )

if(WIN32)
  add_library(uptftopl SHARED ${uptftopl_SRCS})
else()
  add_executable(uptftopl ${uptftopl_SRCS})
endif()

target_compile_definitions(uptftopl
  PRIVATE -DHEX_CHAR_CODE
  )

target_include_directories(uptftopl
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )

#target_link_libraries(uptftopl libukanji ptexenc kpathsea)
target_link_libraries(uptftopl libukanji web2c_libp ptexenc libmd5 zlib web2c_lib kpathsea)

#web2c_convert(uptftopl OUTPUT ${uptftopl_c_h} DEPENDS uptftopl.p ${web2c_texmf} uptexdir/uptex.defines)
web2c_convert(uptftopl OUTPUT ${uptftopl_c_h} DEPENDS uptftopl.p ${web2c_texmf} uptexdir/uptex.defines)

web2c_tangle(uptftopl OUTPUT uptftopl.p DEPENDS uptftopl.web uptexdir/uptftopl.ch)

web2c_tie_m(uptftopl.web SOURCES ${uptftopl_web_srcs})
#web2c_tie_c(uptftopl.ch SOURCES uptftopl.web ${uptftopl_web_srcs})

