set(TEST_HEADERS
    controller.h)

set(TEST_SOURCES
    controller.c)
	
add_library(controller ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(controller view)
