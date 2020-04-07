add_subdirectory(file_reader)
add_subdirectory(game)

set(TEST_HEADERS
    cycle.h)

set(TEST_SOURCES
    cycle.c)
	
add_library(model ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(model game file_reader)
