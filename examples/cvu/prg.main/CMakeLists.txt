
add_executable(cvu_prg_main
	prg.main.c
)

target_link_libraries(cvu_prg_main
	clasp
)

target_compile_options(cvu_prg_main PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic
	>
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
		-Wno-incompatible-pointer-types-discards-qualifiers
	>
	$<$<CXX_COMPILER_ID:GNU>:
		-Wno-incompatible-pointer-types
	>
    $<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)

