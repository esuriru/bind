cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(bind LANGUAGES C CXX)

add_subdirectory(bind)
add_subdirectory(examples)
