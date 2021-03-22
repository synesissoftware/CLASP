
cmake_minimum_required(VERSION 3.0)

project(clasp)

include_directories(include)

add_subdirectory(./projects/clasp.core)

add_subdirectory(./examples/cvu/prg)

add_subdirectory(./examples/cvu/prg.main)

install(TARGETS clasp)

INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")

