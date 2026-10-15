list(APPEND X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	incompatible-pointer-types
	incompatible-pointer-types-discards-qualifiers
)
list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4996
)
define_example_program(test.scratch.C.version main.c)
