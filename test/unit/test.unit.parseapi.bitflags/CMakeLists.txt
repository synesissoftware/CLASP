
add_executable(test.unit.parseapi.bitflags
    test.unit.parseapi.bitflags.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.unit.parseapi.bitflags
    clasp
    xTests::xTests.core
)

target_compile_options(test.unit.parseapi.bitflags PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic

        -Wno-incompatible-pointer-types-discards-qualifiers
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4
    >
)


# ############################## end of file ############################# #

