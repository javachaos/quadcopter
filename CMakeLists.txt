cmake_minimum_required (VERSION 2.6)
project (Quadcopter)
# The version number.
set (Quadcopter_VERSION_MAJOR 0)
set (Quadcopter_VERSION_MINOR 1)
set (CMAKE_CXX_FLAGS "-g -Wall")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/QuadcopterConfig.h.in"
  "${PROJECT_BINARY_DIR}/src/QuadcopterConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find QuadcopterConfig.h
include_directories ( "${PROJECT_BINARY_DIR}" )
include_directories ( "${PROJECT_SOURCE_DIR}/src" )
include_directories ( "${PROJECT_SOURCE_DIR}/src/c_drivers" )

add_subdirectory (src/c_drivers)

file(GLOB SOURCES "src/*.cpp")
#add_library (src/c_drivers)
add_executable (quadcopter ${SOURCES})

target_link_libraries (quadcopter c_drivers)

