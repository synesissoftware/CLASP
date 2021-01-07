
cmake_minimum_required(VERSION 2.8)

project(clasp)

include_directories(include)

add_subdirectory(./projects/clasp.core)

add_subdirectory(./examples/cvu/prg)

add_subdirectory(./examples/cvu/prg.main)

