# Manual: publish found efferents as compile definitions for this
# reporter. Do not restore SIS:AUTO_GENERATED; the generator cannot
# preserve these conditionals.
define_example_program(test.scratch.versions main.cpp)

target_link_libraries(test.scratch.versions
	PRIVATE
		woad::woad
)

if(STLSoft_FOUND OR DEFINED STLSOFT_INCLUDE_DIR)

	target_compile_definitions(test.scratch.versions
		PRIVATE
			STLSoft_FOUND
	)
endif()

if(shwild_FOUND)

	target_compile_definitions(test.scratch.versions
		PRIVATE
			shwild_FOUND
	)

	target_link_libraries(test.scratch.versions
		PRIVATE
			shwild::core
	)
endif()

if(woad_FOUND)

	target_compile_definitions(test.scratch.versions
		PRIVATE
			woad_FOUND
	)
endif()
