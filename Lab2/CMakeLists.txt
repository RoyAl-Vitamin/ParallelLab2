cmake_minimum_required(VERSION 3.9)
project(Lab2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(Lab2 main.c)

target_link_libraries(Lab2 m)