add_subdirectory(model)
add_subdirectory(view)

set(TEST_HEADERS
    define.h
	game.h
	)

set(TEST_SOURCES
    main.c
	game.c
	)
	
add_executable(burp ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(burp model view)
