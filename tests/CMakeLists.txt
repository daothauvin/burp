include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(EXTRA_LIBS m rt pthread)

add_subdirectory(check_file_reader)

set(TEST_HEADERS
	check_header.h
    )

set(TEST_SOURCES
    check_main.c
	)
	
add_executable(check_main ${TEST_HEADERS} ${TEST_SOURCES})

target_link_libraries(check_main check_file_reader ${CHECK_LIBRARIES} ${EXTRA_LIBS})