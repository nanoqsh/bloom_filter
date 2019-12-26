
cmake_minimum_required(VERSION 3.15)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS src/*.hpp)

add_executable(${PROJECT_NAME} src/main.cpp ${HEADERS})
