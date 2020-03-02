cmake_minimum_required(VERSION 3.0)

add_subdirectory(core ${CMAKE_CURRENT_BINARY_DIR}/core-build)

set(gedim_source ${gedim_core_source} PARENT_SCOPE)
set(gedim_headers ${gedim_core_headers} PARENT_SCOPE)
