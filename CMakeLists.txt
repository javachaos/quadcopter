cmake_minimum_required (VERSION 2.6)

SET(CMAKE_BUILD_TYPE distribution)
SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3 -gstabs")
SET(CMAKE_C_FLAGS_DISTRIBUTION "-O3")
SET(CMAKE_CXX_COMPILER "g++")

project (Quadcopter)


# The version number.
set (Quadcopter_VERSION_MAJOR 0)
set (Quadcopter_VERSION_MINOR 1)
set (Quadcopter_VERSION_PATCH 0)
set (Quadcopter_VERSION ${Quadcopter_VERSION_MAJOR}.${Quadcopter_VERSION_MINOR}.${Quadcopter_VERSION_PATCH})

include_directories ( 
  BEFORE "${PROJECT_SOURCE_DIR}/src/c_drivers"
  AFTER  "${PROJECT_SOURCE_DIR}/src" 
  "${PROJECT_BINARY_DIR}"
)

add_subdirectory (src/c_drivers)

file(GLOB SOURCES "src/*.cpp")

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX )

add_executable (quadcopter ${SOURCES})

target_link_libraries (quadcopter c_drivers)

