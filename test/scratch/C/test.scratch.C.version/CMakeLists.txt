
add_executable(test_scratch_C_version
    test.scratch.C.version.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test_scratch_C_version
    clasp
)

target_compile_options(test_scratch_C_version PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic
        -Wno-incompatible-pointer-types-discards-qualifiers
    >
    $<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
)


# ############################## end of file ############################# #

