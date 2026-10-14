define_example_program(test.scratch.versions main.cpp)

target_link_libraries(test.scratch.versions
	PRIVATE
		woad::woad
)
