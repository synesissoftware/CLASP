
add_executable(cvu_prg
	prg.c
)

target_link_libraries(cvu_prg
	clasp
)

target_compile_options(cvu_prg PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
	-Werror -Wall -Wextra -pedantic
	-Wno-incompatible-pointer-types-discards-qualifiers
	-Wno-incompatible-pointer-types
	>
	$<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
)


