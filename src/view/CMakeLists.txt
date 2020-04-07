set(TEST_HEADERS
    ui.h)

set(TEST_SOURCES
    ui.c)
	
add_library(view ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(view game ${CURSES_LIBRARIES})
