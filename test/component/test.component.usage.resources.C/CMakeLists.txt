
add_executable(test.component.usage.resources.C
    test.component.usage.resources.C.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.component.usage.resources.C
    xTests::xTests.core
)

target_compile_options(test.component.usage.resources.C PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4
    >
)


# ############################## end of file ############################# #

