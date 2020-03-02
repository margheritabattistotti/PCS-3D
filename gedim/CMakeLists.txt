cmake_minimum_required(VERSION 3.00)

project(gedim LANGUAGES CXX C)

# CACHE VARIABLES DEFINITION
set(GEDIM_EXTERNAL_BUILD_DIR "" CACHE STRING "Directory where GeDiM external components were built (absolute path)")
set(USE_MPI OFF CACHE BOOL "Enable MPI support")
set(USE_PETSC OFF CACHE BOOL "Enable PETSC support")
set(ENABLE_TRIANGLE OFF CACHE BOOL "Enable VTK support")
set(ENABLE_TETGEN OFF CACHE BOOL "Enable VTK support")
set(ENABLE_VTK OFF CACHE BOOL "Enable VTK support")
set(ENABLE_METIS OFF CACHE BOOL "Enable Metis support")
set(PETSC_ARCH "" CACHE STRING "Set the PETSc compiling architecture")
set(MPI_COMPILER_C mpicc CACHE STRING "C compiler used when USE_MPI is ON")
set(MPI_COMPILER_CXX mpic++ CACHE STRING "C++ compiler used when USE_MPI is ON")
set(VERBOSE 3 CACHE STRING "Select verbosity level (0, 1, 2 3 or 4)")
set_property(CACHE VERBOSE PROPERTY STRINGS 0 1 2 3 4)
if(NOT ${VERBOSE} MATCHES 0 AND NOT ${VERBOSE} MATCHES 1 AND NOT ${VERBOSE} MATCHES 2 AND NOT ${VERBOSE} MATCHES 3 AND NOT ${VERBOSE} MATCHES 4)
	message(SEND_ERROR "VERBOSE variable must be either 0 (None), 1 (Error), 2 (Warning), 3 (Info) or 4 (Debug)")
endif()
set(LOGGING 3 CACHE STRING "Select logging level (0, 1, 2 or 3)")
set_property(CACHE LOGGING PROPERTY STRINGS 0 1 2 3)
if(NOT ${LOGGING} MATCHES 0 AND NOT ${LOGGING} MATCHES 1 AND NOT ${LOGGING} MATCHES 2 AND NOT ${LOGGING} MATCHES 3)
	message(SEND_ERROR "LOGGING variable must be either 0 (None), 1 (Console), 2 (LogFile) or 3 (Console and LogFile)")
endif()

# IMPOSE CXX STANDARD
set(CMAKE_CXX_STANDARD 11)

# IMPOSE COMPILER REGARDLESS OF CACHE VALUE IF MPI SUPPORT IS REQUIRED
if(${USE_MPI})
	set(CMAKE_CXX_COMPILER ${MPI_COMPILER_CXX})
	set(CMAKE_C_COMPILER ${MPI_COMPILER_C})
endif()

# PETSC
if(${USE_PETSC})
	set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/src/external/cmake-modules)
	set( PETSC_EXECUTABLE_RUNS Yes )
	find_package( PETSc REQUIRED )
	set( gedim_include ${gedim_include} ${PETSC_INCLUDES} )
	foreach(petscLib ${PETSC_LIBRARIES})
		get_filename_component(petscLibFileName ${petscLib} NAME_WE)
		get_filename_component(petscLibExt ${petscLib} EXT)
		if(${petscLibExt} MATCHES ".a")
			add_library(petsc_${petscLibFileName} STATIC IMPORTED)
		elseif(${petscLibExt} MATCHES ".so")
			add_library(petsc_${petscLibFileName} SHARED IMPORTED)
		else()
			message(SEND_ERROR "Library extension not recognized for file  ${petscLib}")
		endif()
		set_target_properties(petsc_${petscLibFileName} PROPERTIES IMPORTED_LOCATION ${petscLib})
		set(gedim_libs  ${gedim_libs} petsc_${petscLibFileName})
	endforeach()
	add_definitions( ${PETSC_DEFINITIONS} )
endif()

# ADD SOURCE SUBDIRECTORY
set(gedimBuildDirectory ${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(src ${CMAKE_CURRENT_BINARY_DIR}/src-build)

# COPY HEADERS IN LIBRARY INCLUDE FOLDER AND DEFINE INCLUDE FOLDERS LIST
set(gedim_headers_directory ${CMAKE_CURRENT_BINARY_DIR}/include)
foreach(header ${gedim_headers})
	get_filename_component(headerFileName ${header} NAME_WE)
	get_filename_component(headerExtension ${header} EXT)
	if(${headerExtension} MATCHES ".hpp.in")
		set(headerExtension ".hpp")
	elseif(NOT ${headerExtension} MATCHES ".hpp" AND NOT ${headerExtension} MATCHES ".h")
		message(SEND_ERROR "Header extension not recognized for file ${headerFileName}${headerExtension}")
	endif()
	configure_file(${header} ${gedim_headers_directory}/${headerFileName}${headerExtension})
endforeach()
set(gedim_include ${gedim_include}
	${gedim_headers_directory}
	${GEDIM_EXTERNAL_BUILD_DIR}/eigen/include
	)
if(${ENABLE_VTK})
	set(gedim_include ${gedim_include}
		${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/Common/Core
		${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/IO/XML
		${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/Common/DataModel
		${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/Utilities/KWIML
		${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/Filters/Core
		${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/Common/ExecutionModel
		)
endif()
if(${ENABLE_METIS})
	set(gedim_include ${gedim_include}
		${GEDIM_EXTERNAL_BUILD_DIR}/metis/include
		)
endif()

# DEFINE EXTERNAL LIBRARIES

if(${ENABLE_TRIANGLE})
set(gedim_include ${gedim_include}
	${GEDIM_EXTERNAL_BUILD_DIR}/triangle/include
	)
add_library(triangle STATIC IMPORTED)
set_target_properties(triangle PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/triangle/lib/libtriangle.a)
set(gedim_libs ${gedim_libs} triangle)
endif()

if(${ENABLE_TETGEN})
set(gedim_include ${gedim_include}
	${GEDIM_EXTERNAL_BUILD_DIR}/tetgen/include
	)
add_library(tetgen STATIC IMPORTED)
set_target_properties(tetgen PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/tetgen/lib/libtet.a)
set(gedim_libs ${gedim_libs} tetgen)
endif()

if(${ENABLE_VTK})
	add_library(vtkCommonCore SHARED IMPORTED)
	set_target_properties(vtkCommonCore PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/lib/libvtkCommonCore-7.1.so)
	add_library(vtkIOXML SHARED IMPORTED)
	set_target_properties(vtkIOXML PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/lib/libvtkIOXML-7.1.so)
	add_library(vtkCommonDataModel SHARED IMPORTED)
	set_target_properties(vtkCommonDataModel PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/lib/libvtkCommonDataModel-7.1.so)
	add_library(vtkFiltersCore SHARED IMPORTED)
	set_target_properties(vtkFiltersCore PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/lib/libvtkFiltersCore-7.1.so)
	add_library(vtkCommonExecutionModel SHARED IMPORTED)
	set_target_properties(vtkCommonExecutionModel PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/vtk/VTK-7.1.1/lib/libvtkCommonExecutionModel-7.1.so)
	set(gedim_libs ${gedim_libs} vtkCommonCore vtkIOXML vtkCommonDataModel vtkFiltersCore vtkCommonExecutionModel)
endif()
if(${ENABLE_METIS})
	add_library(metis STATIC IMPORTED)
	set_target_properties(metis PROPERTIES IMPORTED_LOCATION ${GEDIM_EXTERNAL_BUILD_DIR}/metis/lib/libmetis.a)
	set(gedim_libs ${gedim_libs} metis)
endif()

# INCLUDE DIRECTORIES
include_directories(${gedim_include})

# CREATE LIBRARY
add_library( ${PROJECT_NAME} STATIC ${gedim_source} )

if (NOT ${gedim_libs})
add_dependencies( ${PROJECT_NAME} ${gedim_libs} )
target_link_libraries( ${PROJECT_NAME} ${gedim_libs} )
endif()

set_target_properties( ${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/ )

# the parent scope (if any) will have the ${gedim_include} containing the directories to be included for using GeDiM
get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
	set(gedim_include ${gedim_include} PARENT_SCOPE)
endif()
