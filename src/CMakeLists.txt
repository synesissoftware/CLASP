
SET (CORE_SRC_DIR .)

SET (CORE_SRCS
    ${CORE_SRC_DIR}/clasp.api.c
    ${CORE_SRC_DIR}/clasp.usage.FILE.c
    ${CORE_SRC_DIR}/clasp.string.c
    ${CORE_SRC_DIR}/clasp.usage.c
    ${CORE_SRC_DIR}/clasp.core.c
    ${CORE_SRC_DIR}/clasp.diagnostics.c
    ${CORE_SRC_DIR}/clasp.memory.c
)

add_library(clasp ${CORE_SRCS})

if (APPLE)

    message("-- -- adding '/usr/local/include' to include-directories for 'src'")

    include_directories("/usr/local/include")
endif()

if(UNIX)

    add_definitions(-DUNIX)
    add_definitions(-Dunix)
endif(UNIX)

if(WIN32)

    message(FATAL_ERROR "Use of CMake on Windows not currently supported")
endif(WIN32)


set(CORE_PUBLIC_HEADERS
    "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/${PROJECT_NAME_LOWER}.h"
)

set_target_properties(clasp PROPERTIES
    OUTPUT_NAME "clasp"
    PUBLIC_HEADER "${CORE_PUBLIC_HEADERS}"
)


# include_directories(include)


target_include_directories(clasp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(clasp PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Werror -Wall -Wextra -pedantic
    >
    $<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
)

