cmake_minimum_required(VERSION 3.0)

project(PPC LANGUAGES CXX C)

# ADD GEDIM SUBDIRECTORY
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/gedim ${CMAKE_CURRENT_BINARY_DIR}/gedim )

# ADD TEST
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

set(headers_directory ${CMAKE_CURRENT_BINARY_DIR}/include/)
file(MAKE_DIRECTORY ${headers_directory})
foreach(header ${aux_headers})
    configure_file(${header} ${headers_directory})
endforeach()
include_directories(${headers_directory})

# INCLUDE DIRECTORIES
include_directories(${gedim_include})

# CREATE_EXECUTABLE
add_executable(${PROJECT_NAME} main.cpp ${aux_sources})
target_link_libraries(${PROJECT_NAME} gedim)

