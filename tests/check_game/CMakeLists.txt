include_directories(${CHECK_INCLUDE_DIRS})

link_directories(${CHECK_LIBRARY_DIRS})

set(EXTRA_LIBS m rt pthread)

set(TEST_SOURCES
   	check_commands.c
    check_missiles.c
    check_robot.c
    check_arena.c)

add_library(check_game ${TEST_SOURCES})
target_link_libraries(check_game game ${CHECK_LIBRARIES} ${EXTRA_LIBS})