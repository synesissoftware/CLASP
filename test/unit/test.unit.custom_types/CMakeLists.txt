
add_executable(test.unit.custom_types
	test.unit.custom_types.cpp
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.unit.custom_types
	clasp
	xTests::xTests.core
)

target_compile_options(test.unit.custom_types PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic

		-Wno-incompatible-pointer-types-discards-qualifiers
		-Wno-writable-strings
	>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)


# ############################## end of file ############################# #

