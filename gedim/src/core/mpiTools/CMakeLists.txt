cmake_minimum_required(VERSION 3.0)

set(gedim_core_mpiTools_source
        ${CMAKE_CURRENT_SOURCE_DIR}/MPI_Process.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ParallelEnvironment.cpp
	PARENT_SCOPE)

set(gedim_core_mpiTools_headers
        ${CMAKE_CURRENT_SOURCE_DIR}/MPI_Process.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ParallelEnvironment.hpp
	PARENT_SCOPE)
