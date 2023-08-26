

## e-TeX SyncTeX

set(etex_include_synctex
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/synctexdir"
  )

set(etex_link_synctex
  zlib
  )

set(etex_ch_synctex
  synctexdir/synctex-def.ch0
  synctexdir/synctex-mem.ch0
  synctexdir/synctex-e-mem.ch0
  synctexdir/synctex-e-mem.ch1
  synctexdir/synctex-rec.ch0
  synctexdir/synctex-rec.ch1
  synctexdir/synctex-e-rec.ch0
  )

set(dist_etex_SOURCES_synctex
  synctexdir/synctex.c
  synctexdir/synctex.h
  synctexdir/synctex-common.h
  synctexdir/synctex-etex.h
  )

set(etex_definitions_synctex
  PRIVATE -D__SyncTeX__
  PRIVATE -DSYNCTEX_ENGINE_H=\"synctex-etex.h\"
  )

# e-pTeX

set(etex_c_h
  etexini.c
  etex0.c
  etexcoerce.h
  etexd.h
  )

set(nodist_etex_SOURCES
  ${etex_c_h}
  etex-pool.c
  )

set(dist_etex_SOURCES
  etexdir/etexextra.c
  etexdir/etexextra.h
  etexdir/etex_version.h
  ${dist_etex_SOURCES_synctex}
  )

set(etex_web_srcs
  tex.web
  etexdir/etex.ch
  etexdir/tex.ch0
  tex.ch
  zlib-fmt.ch
  )

set(etex_ch_srcs
  enctexdir/enctex1.ch
  enctexdir/enctex-tex.ch
  enctexdir/enctex2.ch
  ${etex_ch_synctex}
  etexdir/tex.ch1
  etexdir/tex.ech
  tex-binpool.ch
  )

set(etex_SRCS
  ${nodist_etex_SOURCES}
  ${dist_etex_SOURCES}
  )

if(WIN32)
  add_library(etex SHARED ${etex_SRCS})
else()
  add_executable(etex ${etex_SRCS})
endif()

target_compile_definitions(etex ${etex_definitions_synctex})

target_include_directories(etex
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libmd5"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  ${etex_include_synctex}
  )

target_link_libraries(etex libmd5 zlib web2c_lib kpathsea ${etex_link_synctex})

web2c_convert(etex OUTPUT ${etex_c_h} DEPENDS etex.p ${web2c_texmf})

web2c_texmf_tangle(etex OUTPUT etex.p etex.pool DEPENDS etex.web etex.ch)

web2c_tie_m(etex.web SOURCES ${etex_web_srcs})
web2c_tie_c(etex.ch SOURCES etex.web ${etex_ch_srcs})

add_custom_command(
  OUTPUT etex-pool.c
  DEPENDS etex.pool etexd.h makecpool
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/cmake/makecpool.py"
    "--makecpool" "$<TARGET_FILE:makecpool>"
    etex etex-pool.c
  )

if(WIN32)
  add_executable(calldll_etex "cmake/calldll.c")
  target_compile_definitions(calldll_etex PRIVATE DLLPROC=dlletexmain)
  target_link_libraries(calldll_etex etex)

  foreach(name ptex etex platex)
    add_custom_command(TARGET calldll_etex POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:calldll_etex>"
        "$<TARGET_FILE_DIR:calldll_etex>/${name}.exe"
      )
  endforeach()
endif()
