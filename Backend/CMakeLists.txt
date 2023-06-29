cmake_minimum_required(VERSION 3.10)

project(Banking)

file(GLOB SOURCES src/*.cc)
file(GLOB headers src/*.hh)

include_directories(include)

add_executable(Banking Banking.cc ${SOURCES})
target_link_libraries(Banking LINK_PUBLIC sqlite3)