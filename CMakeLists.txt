cmake_minimum_required(VERSION 3.3)
project(c_code)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

#set(SOURCE_FILES h4_driver.c)
file(GLOB all_files "*.c")

#add_executable(c_code ${SOURCE_FILES})
add_executable(cs315 ${all_files} cs315/x86/h04/h4_driver.c)
