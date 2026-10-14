list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4996
)
define_automated_test_program(test.unit.main.programname.C entry.c)

target_link_libraries(test.unit.main.programname.C
	PRIVATE
		woad::woad
)
