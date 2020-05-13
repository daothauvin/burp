set(TEST_HEADERS
    controler.h)

set(TEST_SOURCES
    controler.c)
	
add_library(controler ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(controler view)
