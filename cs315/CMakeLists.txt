cmake_minimum_required(VERSION 3.3)
project(cs315)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES h4_driver.c)
#file(GLOB all_files "*.c")

add_executable(cs315 ${SOURCE_FILES})
#add_executable(cs315 ${all_files} cs315/h04/h4_driver.c)
