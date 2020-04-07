include_directories(${CHECK_INCLUDE_DIRS})

link_directories(${CHECK_LIBRARY_DIRS})

set(FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test_files")

configure_file(check_file_reader.h.in "${CMAKE_CURRENT_SOURCE_DIR}/check_file_reader.h" @ONLY)

set(EXTRA_LIBS m rt pthread)

set(TEST_SOURCES
   	check_file_reader.c)
	
set(TEST_HEADERS
	check_file_reader.h
    )

add_library(check_file_reader ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(check_file_reader file_reader ${CHECK_LIBRARIES} ${EXTRA_LIBS})

target_include_directories(check_file_reader
    PRIVATE
    ${CMAKE_BINARY_DIR})