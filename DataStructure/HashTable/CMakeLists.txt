cmake_minimum_required(VERSION 3.5)

project (hash_table)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/main.cpp
	src/HashTable.cpp
	src/HashObject.cpp
)

add_executable(hash_table ${SOURCES})

target_include_directories(hash_table
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)