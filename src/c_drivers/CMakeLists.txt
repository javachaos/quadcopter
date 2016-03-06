cmake_minimum_required(VERSION 2.8.9)
project(c_drivers)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "*.c")

#Generate the shared library from the sources
include_directories(${PYTHON_INCLUDE_DIRS})
find_package(PythonLibs REQUIRED)
add_library(c_drivers SHARED ${SOURCES})

#target_link_libraries(${PYTHON_INCLUDE_DIRS} c_drivers)
target_include_directories(c_drivers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PYTHON_INCLUDE_DIRS})

