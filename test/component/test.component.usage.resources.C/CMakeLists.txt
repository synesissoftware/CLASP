
add_executable(test.component.usage.resources.C
	entry.c
	$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:test.component.usage.resources.rc>
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.component.usage.resources.C
	PRIVATE
		core
		$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
		$<IF:$<VERSION_LESS:${xTests_VERSION},"0.23">,xTests::xTests.core,xTests::core>
)

target_compile_options(test.component.usage.resources.C PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic
	>
	$<$<CXX_COMPILER_ID:GNU>:
		-Wno-incompatible-pointer-types
		-Wno-unused-but-set-variable
	>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)


# ############################## end of file ############################# #

