# cweb.cmake

add_executable(tie tie.c)

if(MSVC)
  target_compile_definitions(tie PRIVATE -D_CRT_SECURE_NO_WARNINGS=1)
endif()

target_include_directories(tie
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  )

target_link_libraries(tie web2c_lib kpathsea)

add_custom_command(
  OUTPUT tie.c
  BYPRODUCTS tie.c
  DEPENDS ctangle tiedir/tie.w tiedir/tie-w2c.ch
  COMMAND ${CMAKE_COMMAND} -E env
    "CWEBINPUTS=${CMAKE_CURRENT_SOURCE_DIR}/tiedir"
    "TEXMFCNF=${CMAKE_CURRENT_SOURCE_DIR}/../kpathsea"
    "$<TARGET_FILE:ctangle>" tie.w tie-w2c.ch
  )


foreach(name dvicopy dvitype gftodvi gftopk gftype mft patgen pktogf pktype pooltype tftopl vftovp vptovf weave)

  add_executable(${name} ${name}.c)

  if(MSVC)
    target_compile_definitions(${name} PRIVATE -D_CRT_SECURE_NO_WARNINGS=1)
  endif()

  target_include_directories(${name}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    )

  target_link_libraries(${name} web2c_lib kpathsea)

  web2c_convert(${name} OUTPUT ${name}.c DEPENDS ${name}.p)

  web2c_texmf_tangle(${name} OUTPUT ${name}.p DEPENDS ${name}.web ${name}.ch)

endforeach()
