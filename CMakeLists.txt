cmake_minimum_required(VERSION 3.0)
project(chat)

#set compiling args
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#set .exe file's ultimate output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#set head file's path
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

#upload subdirectory
add_subdirectory(src)