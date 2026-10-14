define_automated_test_program(test.unit.main.programname.1 entry.cpp)

target_link_libraries(test.unit.main.programname.1
	PRIVATE
		woad::woad
)
