cmake_minimum_required(VERSION 3.3)
project(c_code)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

file(GLOB all_files "*.c")

add_executable(c_code ${all_files} cs315/h04/h4_driver.c)
