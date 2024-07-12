
add_executable(cvu_prg_main
	prg.main.c
)

target_link_libraries(cvu_prg_main
	PRIVATE
		core
)

target_compile_options(cvu_prg_main PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Werror -Wall -Wextra -pedantic>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)

