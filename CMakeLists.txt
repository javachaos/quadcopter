cmake_minimum_required (VERSION 2.8.9)
SET(CMAKE_BUILD_TYPE distribution)
IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "Intel")
    SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
ELSE()
    SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3 -mfpu=neon -mfloat-abi=hard")
ENDIF()

#-mfpu=neon -mfloat-abi=hard
SET(CMAKE_C_FLAGS_DISTRIBUTION "-O3")
SET(CMAKE_CXX_COMPILER "g++")
SET(INSTALL_HOME "/usr/sbin/")
SET(PY_INSTALL_HOME "/usr/local/lib/python2.7/dist-packages/")
SET(SYSCTL "systemctl")
SET(SERVICE_FILE "quadcopter.service")
SET(SYSTEM_D_HOME   "/etc/systemd/system/")
project (Quadcopter)

# The version number.
set (Quadcopter_VERSION_MAJOR 0)
set (Quadcopter_VERSION_MINOR 1)
set (Quadcopter_VERSION_PATCH 0)
set (Quadcopter_VERSION ${Quadcopter_VERSION_MAJOR}.${Quadcopter_VERSION_MINOR}.${Quadcopter_VERSION_PATCH})
set (DEBUG 1)
MESSAGE("Using GCC Options:".${CMAKE_CXX_FLAGS_DISTRIBUTION})
#SET(CMAKE_VERBOSE_MAKEFILE 1)
SET(SYSTEM_D_LOADER "${PROJECT_SOURCE_DIR}/src/${SERVICE_FILE}")
SET(SHARED_LIBS "${PROJECT_BINARY_DIR}/src/c_drivers/libc_drivers.so")
SET(LIB_INSTALL_HOME "/usr/local/lib/")

find_package(Boost REQUIRED COMPONENTS system)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/QuadcopterConfig.h.in"
  "${PROJECT_BINARY_DIR}/QuadcopterConfig.h"
  )

include_directories ( 
  BEFORE "${PROJECT_SOURCE_DIR}/src/c_drivers"
  AFTER  "${PROJECT_SOURCE_DIR}/src" 
  "${PROJECT_BINARY_DIR}"
  "${Boost_INCLUDE_DIRS}"
)

link_directories(${Boost_LIBRARY_DIRS})


add_subdirectory (src/c_drivers)
file(GLOB SOURCES "src/*.cpp")
file(GLOB PY_SOURCES "src/python/*.py")
set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX )
add_executable (quadcopter ${SOURCES})
target_link_libraries (quadcopter ${Boost_LIBRARIES} c_drivers)
#target_link_libraries (quadcopter c_drivers)
set_target_properties(quadcopter PROPERTIES INSTALL_RPATH ${LIB_INSTALL_HOME})

#install (CODE "execute_process(COMMAND \"${SYSCTL} stop ${SERVICE_FILE}\")")
install (TARGETS quadcopter DESTINATION ${INSTALL_HOME})
install (FILES ${SHARED_LIBS} DESTINATION ${LIB_INSTALL_HOME})
install (FILES ${SYSTEM_D_LOADER} DESTINATION ${SYSTEM_D_HOME})
install (FILES ${PY_SOURCES} DESTINATION ${PY_INSTALL_HOME})
#install (CODE "execute_process(COMMAND \"${SYSCTL} start ${SERVICE_FILE}\")")
