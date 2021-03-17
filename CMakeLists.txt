cmake_minimum_required(VERSION 3.10)

project(ModernSqlite)

file(GLOB SRC_FILE "./src/*.cpp")
file(GLOB HEAD_FILE "./src/*.h")

file(GLOB SQLITE_SRC_FILE "./sqlite3/*.c")
file(GLOB SQLITE_HEAD_FILE "./sqlite3/*.h")

add_executable(ModernSqlite 
	${SRC_FILE} 
	${HEAD_FILE}
)

#add_library(sqlite3 
	#SHARED
	#${SQLITE_SRC_FILE}
	#${SQLITE_HEAD_FILE}
#)

#link_libraries(ModernSqlite
#PRIVATE
#	sqlite3
#)


