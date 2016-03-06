cmake_minimum_required(VERSION 2.8.9)
project(c_drivers)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "*.c")
 
#Generate the shared library from the sources
add_library(c_drivers STATIC ${SOURCES})

target_include_directories (c_drivers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

