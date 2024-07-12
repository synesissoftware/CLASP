
add_executable(test.unit.main.exceptions
	test.unit.main.exceptions.cpp
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.unit.main.exceptions
	PRIVATE
		core
		xTests::xTests.core
)

target_compile_options(test.unit.main.exceptions PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic

		-Wno-incompatible-pointer-types-discards-qualifiers
	>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4

		/wd4996
	>
)


# ############################## end of file ############################# #

