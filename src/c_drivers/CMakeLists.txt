cmake_minimum_required(VERSION 2.8.9)
project(c_drivers)

file(GLOB CSOURCES "*.c")

find_package(PythonLibs 2.7 REQUIRED)

#Generate the shared library from the sources
include_directories(${PYTHON_INCLUDE_DIRS})
set_source_files_properties(${CSOURCES} PROPERTIES LANGUAGE CXX )
add_library(c_drivers SHARED ${CSOURCES})
MESSAGE(${PYTHON_INCLUDE_DIRS})
target_link_libraries(c_drivers ${PYTHON_LIBRARIES})
