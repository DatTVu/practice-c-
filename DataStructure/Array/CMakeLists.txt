cmake_minimum_required(VERSION 3.5)

project (dynamic_array)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/main_test.cpp
	src/DynamicArray.cpp
)

add_executable(dynamic_array ${SOURCES})

target_include_directories(dynamic_array
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)