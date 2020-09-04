cmake_minimum_required(VERSION 3.5)

project (array_queue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/main_test.cpp
	src/ArrayQueue.cpp
)

add_executable(array_queue ${SOURCES})

target_include_directories(array_queue
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)