cmake_minimum_required(VERSION 3.10)
project(RTIOW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(main src/main.cc) 

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)