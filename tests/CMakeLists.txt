set(TEST_HEADERS
    )

set(TEST_SOURCES
    check_file_reader.c)
	
add_executable(check_file_reader ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(check_file_reader model)
