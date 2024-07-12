
add_executable(test.component.searchspecs.C
	test.component.searchspecs.C.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.component.searchspecs.C
	PRIVATE
		core
		$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
		xTests::xTests.core
)

target_compile_options(test.component.searchspecs.C PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic
	>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)


# ############################## end of file ############################# #

