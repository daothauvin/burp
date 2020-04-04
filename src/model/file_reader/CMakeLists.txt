set(TEST_HEADERS
    interpreter.h
	syntax_analyse.h
	syntax_tree.h)

set(TEST_SOURCES
    interpreter.c
	syntax_analyse.c)
	
add_library(file_reader ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(file_reader game ${GLIB_LIBRARIES})
