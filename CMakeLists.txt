
cmake_minimum_required(VERSION 3.15)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC src/*)

add_executable(${PROJECT_NAME} ${SRC})
