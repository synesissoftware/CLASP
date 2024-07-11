
add_executable(test.unit.parseapi.findflagoroption
	test.unit.parseapi.findflagoroption.c
)

link_directories(${CMAKE_SOURCE_DIR}/projects/core)

target_link_libraries(test.unit.parseapi.findflagoroption
	clasp
	xTests::xTests.core
)

target_compile_options(test.unit.parseapi.findflagoroption PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic

		-Wno-incompatible-pointer-types-discards-qualifiers
	>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)


# ############################## end of file ############################# #

