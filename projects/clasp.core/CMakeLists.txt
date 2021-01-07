
SET (CORE_SRC_DIR ../../src)

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


target_compile_options(clasp PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Werror -Wall -Wextra -pedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
    )


