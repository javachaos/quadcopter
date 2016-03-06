cmake_minimum_required(VERSION 2.8.9)
project(c_drivers)

set(CMAKE_C_FLAGS "-Wno-unused-result -DDYNAMIC_ANNOTATIONS_ENABLED=1 -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic")
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "*.c")

find_package(PythonLibs 2.7 REQUIRED)

#Generate the shared library from the sources
include_directories(${PYTHON_INCLUDE_DIRS})
add_library(c_drivers SHARED ${SOURCES})
MESSAGE(${PYTHON_INCLUDE_DIRS})
#target_link_libraries(${PYTHON_INCLUDE_DIRS} c_drivers)
target_include_directories(c_drivers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(c_drivers ${PYTHON_LIBRARIES})
