set(TEST_HEADERS
    arene.h
	commands.h
	missile.h
	robot.h)

set(TEST_SOURCES
    arene.c
	commands.c
	missile.c
	robot.c)
	
add_library(game ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(game m)
