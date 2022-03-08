cmake_minimum_required(VERSION 3.10)

project(ics)

file(GLOB PROJECT_FILES src/*)

add_executable(ics ${PROJECT_FILES})
target_compile_options(ics PRIVATE -g)
