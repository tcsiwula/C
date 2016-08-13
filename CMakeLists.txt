cmake_minimum_required(VERSION 3.3)
project(c_code)

file(GLOB all_files "*.c")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

SET(SOURCE_FILES cs220/fall_2014/h1/h1.c)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
