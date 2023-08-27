# CMakeLists.txt for gregorio directory

set(VERSION "6.0.0")
set(PACKAGE_URL "http://gregorio-project.github.io/")

include(cmake/config.cmake)

get_property(KPATHSEA_INCLUDES GLOBAL PROPERTY KPATHSEA_INCLUDES)

include_directories(${KPATHSEA_INCLUDES})

set(GREGORIO_TREE gregorio-src)

set(gregorio_SOURCES
  ${GREGORIO_TREE}/src/characters.c
  ${GREGORIO_TREE}/src/gregorio-utils.c
  ${GREGORIO_TREE}/src/messages.c
  ${GREGORIO_TREE}/src/sha1.c
  ${GREGORIO_TREE}/src/struct.c
  ${GREGORIO_TREE}/src/support.c
  ${GREGORIO_TREE}/src/unicode.c
  ${GREGORIO_TREE}/src/dump/dump.c
  ${GREGORIO_TREE}/src/gabc/gabc-elements-determination.c
  ${GREGORIO_TREE}/src/gabc/gabc-glyphs-determination.c
  ${GREGORIO_TREE}/src/gabc/gabc-notes-determination-l.c
  ${GREGORIO_TREE}/src/gabc/gabc-score-determination.c
  ${GREGORIO_TREE}/src/gabc/gabc-score-determination-l.c
  ${GREGORIO_TREE}/src/gabc/gabc-score-determination-y.c
  ${GREGORIO_TREE}/src/gabc/gabc-write.c
  ${GREGORIO_TREE}/src/gregoriotex/gregoriotex-position.c
  ${GREGORIO_TREE}/src/gregoriotex/gregoriotex-write.c
  ${GREGORIO_TREE}/src/vowel/vowel.c
  ${GREGORIO_TREE}/src/vowel/vowel-rules-l.c
  ${GREGORIO_TREE}/src/vowel/vowel-rules-y.c
  ${GREGORIO_TREE}/src/config.h
  )

add_executable(gregorio ${gregorio_SOURCES})

target_include_directories(gregorio
  PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
  PRIVATE "${GREGORIO_TREE}/src"
  PUBLIC "${KPATHSEA_INCLUDES}"
  )

target_compile_definitions(gregorio PRIVATE -D_GNU_SOURCE -DUSE_KPSE -DYY_NO_UNISTD_H
  -I${GREGORIO_TREE}/src
  -I${GREGORIO_TREE}/src/gabc
  -I${GREGORIO_TREE}/src/dump
  -I${GREGORIO_TREE}/src/gregoriotex
  )

target_link_libraries(gregorio kpathsea)
