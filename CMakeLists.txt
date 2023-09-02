# CMakeLists.txt for source directory

cmake_minimum_required(VERSION 3.12)

project(texlive)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")

if(MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1)
endif()

set(TEX_LIVE_VERSION "2023/dev")

add_subdirectory(libs)
add_subdirectory(texk)
