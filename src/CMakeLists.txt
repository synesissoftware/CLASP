
# ######################################################################## #
# File:     /src/CMakeLists.txt
#
# Purpose:  CMake lists file for CLASP core library
#
# Created:  ...
# Updated:  19th September 2026
#
# ######################################################################## #


if(UNIX)

	add_definitions(-DUNIX)
	add_definitions(-Dunix)
endif(UNIX)

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		message (STATUS "Compiling for 64-bit Windows")

		add_definitions(-DWIN64)
	else()

		message (STATUS "Compiling for 32-bit Windows")

		add_definitions(-DWIN32)
	endif()

	# suppress implicit-link file
	add_definitions(-DCSTRING_INCL_CSTRING_H_IMPLICIT_LINK)

	add_definitions(-DCLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS)
endif(WIN32)

if((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))

	add_compile_options("/Zc:__cplusplus")

	add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
endif()


SET (CORE_SRC_DIR .)

SET (CORE_SRCS
	${CORE_SRC_DIR}/clasp.api.c
	${CORE_SRC_DIR}/clasp.core.c
	${CORE_SRC_DIR}/clasp.diagnostics.c
	${CORE_SRC_DIR}/clasp.memory.c
	${CORE_SRC_DIR}/clasp.string.c
	${CORE_SRC_DIR}/clasp.usage.FILE.c
	${CORE_SRC_DIR}/clasp.usage.c
)

add_library(core
	${CORE_SRCS}
)


# specify the primary public headers for the library, which controls whether
# they'll be installed
#
# NOTE: it is not yet known (to me, at least) how to include additional
# header files from sub-directories, so this is done below in an additional
# `install()` step
set(CORE_PUBLIC_HEADERS
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/${PROJECT_NAME_LOWER}.h"
)

set_target_properties(core PROPERTIES
	OUTPUT_NAME "clasp"
	PUBLIC_HEADER "${CORE_PUBLIC_HEADERS}"
)

target_include_directories(core
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

if(NOT NO_CLASP_CPP_API)

	target_link_libraries(core
		PRIVATE
			$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
	)

	if(DEFINED STLSOFT_INCLUDE_DIR)

		target_include_directories(core
			PUBLIC
				${STLSOFT_INCLUDE_DIR}
		)
	endif()
endif()


target_compile_options(core
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra -pedantic
		>
		$<$<CXX_COMPILER_ID:MSVC>:
			/WX /W4
		>
)


# ##########################################################
# install

install(TARGETS core
	EXPORT project-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER}
)

# for now, we just include xtests.h, as it's not clear how to use the
# PUBLIC_HEADER mechanism to install files into subdirectories (such as xtests/util/temp_file.hpp)

# additional headers into specific sub-directories

if(NO_CLASP_CPP_API)

	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/include/
		DESTINATION include
		FILES_MATCHING
		PATTERN "*.h"
	)
else(NO_CLASP_CPP_API)

	install(
		DIRECTORY ${CMAKE_SOURCE_DIR}/include/
		DESTINATION include
		FILES_MATCHING
		PATTERN "*.h*"
	)
endif(NO_CLASP_CPP_API)


# ############################## end of file ############################# #

