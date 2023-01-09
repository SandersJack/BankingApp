cmake_minimum_required(VERSION 3.10)

project(Banking)

file(GLOB SOURCES src/*.cc)
file(GLOB headers src/*.hh)


add_executable(Banking Banking.cc ${SOURCES})

include_directories(include)