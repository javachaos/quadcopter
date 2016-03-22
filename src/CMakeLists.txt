cmake_minimum_required (VERSION 2.8.9)
project (Quadcopter)

SET(CMAKE_BUILD_TYPE distribution)

SET(ARCH ${CMAKE_SYSTEM_PROCESSOR})
IF(${ARCH} MATCHES "^x86_64$")
    SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-g -std=c++0x")
    SET(CMAKE_C_FLAGS_DISTRIBUTION "-g")
ENDIF(${ARCH} MATCHES "^x86_64$")
IF(${ARCH} MATCHES "^armv7l$")
    SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-Wall -O3 -std=c++0x -mfpu=neon -mfloat-abi=hard")
    SET(CMAKE_C_FLAGS_DISTRIBUTION "-Wall -O3 -mfpu=neon -mfloat-abi=hard")
ENDIF(${ARCH} MATCHES "^armv7l$")

SET(INSTALL_HOME "/usr/sbin/")
SET(PY_INSTALL_HOME "/usr/local/lib/python2.7/dist-packages/")
SET(SYSCTL "systemctl")
SET(SERVICE_FILE "quadcopter.service")
SET(SYSTEM_D_HOME   "/etc/systemd/system/")

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake")

# The version number.
SET(Quadcopter_VERSION_MAJOR 0)
SET(Quadcopter_VERSION_MINOR 1)
SET(Quadcopter_VERSION_PATCH 0)
SET(Quadcopter_VERSION ${Quadcopter_VERSION_MAJOR}.${Quadcopter_VERSION_MINOR}.${Quadcopter_VERSION_PATCH})
SET(DEBUG 1)
MESSAGE("Arch: " ${ARCH})
MESSAGE("Using compiler: " ${CMAKE_CXX_COMPILER})
MESSAGE("Using GCC Options: " ${CMAKE_CXX_FLAGS_DISTRIBUTION})

SET(CMAKE_VERBOSE_MAKEFILE 1)
SET(SYSTEM_D_LOADER "${PROJECT_SOURCE_DIR}/${SERVICE_FILE}")
SET(SHARED_LIBS "${PROJECT_BINARY_DIR}/c_drivers/libc_drivers.so")
SET(LIB_INSTALL_HOME "/usr/local/lib/")

find_package(LZMA)

configure_file (
  "${PROJECT_SOURCE_DIR}/QuadcopterConfig.h.in"
  "${PROJECT_BINARY_DIR}/QuadcopterConfig.h"
  )

include_directories ( 
  BEFORE "${PROJECT_SOURCE_DIR}/c_drivers"
  AFTER  "${PROJECT_SOURCE_DIR}" 
  "${PROJECT_BINARY_DIR}"
  "${LZMA_INCLUDE_DIR}"
)

add_subdirectory (c_drivers)
file(GLOB SOURCES "*.cpp")
file(GLOB PY_SOURCES "python/*.py")
set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX )
add_executable (quadcopter ${SOURCES})
target_link_libraries (quadcopter ${LZMA_LIBRARIES} c_drivers)
set_target_properties(quadcopter PROPERTIES INSTALL_RPATH ${LIB_INSTALL_HOME})

install (TARGETS quadcopter DESTINATION ${INSTALL_HOME})
install (FILES ${SHARED_LIBS} DESTINATION ${LIB_INSTALL_HOME})
install (FILES ${SYSTEM_D_LOADER} DESTINATION ${SYSTEM_D_HOME})
install (FILES ${PY_SOURCES} DESTINATION ${PY_INSTALL_HOME})

