cmake_minimum_required(VERSION 3.10)

project(hab)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(rs232 STATIC src/serial_port/rs232.c)
add_library(serial STATIC src/serial_port/serial.cpp)
add_library(counter STATIC src/counter/counter.cpp)

add_executable(hab src/hab.cpp)
target_link_libraries(serial rs232)
target_link_libraries(hab rs232 serial counter)