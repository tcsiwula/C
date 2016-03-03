cmake_minimum_required(VERSION 3.3)
project(cs220)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

file(GLOB all_files "*.c")

add_executable(cs220 ${all_files})
