cmake_minimum_required(VERSION 3.8)

project(createTableTest)

file(GLOB SRC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(createTableTest 
	${SRC_FILE} 
)

target_include_directories(createTableTest 
PRIVATE
	${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(createTableTest 
PRIVATE
	MSqlite3
)


