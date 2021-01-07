
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

if(MSVC)
	target_compile_options(clasp PRIVATE /W4 /WX)
else()
	target_compile_options(clasp PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

