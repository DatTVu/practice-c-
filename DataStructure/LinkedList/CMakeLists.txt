cmake_minimum_required(VERSION 3.5)

project (linked_list)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/main_test.cpp
	src/LinkedList.cpp
)

add_executable(linked_list ${SOURCES})

target_include_directories(linked_list
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)