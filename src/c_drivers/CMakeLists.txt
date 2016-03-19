cmake_minimum_required(VERSION 2.8.9)
project(c_drivers)
file(GLOB CSOURCES "*.c")
find_package(PythonLibs 2.7 REQUIRED)

include_directories(
    BEFORE "${PROJECT_SOURCE_DIR}"  
    AFTER "${PYTHON_INCLUDE_DIRS}"
)

set_source_files_properties(${CSOURCES} PROPERTIES LANGUAGE CXX )
add_library(c_drivers SHARED ${CSOURCES})
target_link_libraries(c_drivers ${PYTHON_LIBRARIES})
