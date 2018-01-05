cmake_minimum_required(VERSION 3.8)
project(htsim)

enable_language(C CXX)

# The version number.
set (HTSIM_VERSION_MAJOR 1)
set (HTSIM_VERSION_MINOR 0)
set (HTSIM_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 98)

# detect operating system
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
# detect host processor
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/config.h.in"
  "${PROJECT_BINARY_DIR}/src/main/include/config.h"
  )

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/include)

set(SOURCE_CPP_FILES
        ${SOURCE_DIR}/main.cpp
		${SOURCE_DIR}/SimulationConfiguration.cpp
		${SOURCE_DIR}/ConfigurationReader.cpp
		${SOURCE_DIR}/HeatTransferSolver.cpp
		${SOURCE_DIR}/AnalyticSolver.cpp
		${SOURCE_DIR}/ExportUtils.cpp
		${SOURCE_DIR}/StationarySolver.cpp
		${SOURCE_DIR}/NonStationarySolver.cpp
		)

set(INCLUDE_FILES 
		${INCLUDE_DIR}/SimulationConfiguration.h
		${INCLUDE_DIR}/ConfigurationReader.h
		${INCLUDE_DIR}/HeatTransferSolver.h
		${INCLUDE_DIR}/AnalyticSolver.h
		${INCLUDE_DIR}/ExportUtils.h
		${INCLUDE_DIR}/StationarySolver.h
		${INCLUDE_DIR}/NonStationarySolver.h
		)
		
add_executable(htsim ${SOURCE_CPP_FILES})

target_include_directories(htsim PUBLIC ${INCLUDE_DIR})