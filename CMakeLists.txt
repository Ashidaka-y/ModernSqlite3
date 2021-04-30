cmake_minimum_required(VERSION 3.8)

project(MSqlite3)

message(STATUS "Building MSqlite3 Library")

file(GLOB MSQLITE_SRC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB MSQLITE_HAD_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

file(GLOB SQLITE_SRC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/sqlite3/*.c")
file(GLOB SQLITE_HAD_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/sqlite3/*.h")

add_library(MSqlite3 
	SHARED
	${MSQLITE_SRC_FILE}
	${MSQLITE_HAD_FILE}

	${SQLITE_SRC_FILE}
	${SQLITE_HAD_FILE}
)

add_definitions( -DSHARED_LIB)

target_include_directories(MSqlite3
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/sqlite3
)

add_subdirectory("./test/createTable")


