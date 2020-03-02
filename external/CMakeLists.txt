cmake_minimum_required(VERSION 3.0)

set( ENABLE_VTK OFF CACHE BOOL "Enable VTK compilation" )
set( USE_METIS OFF	CACHE BOOL "Enable Metis compilation" )

set( subdirectories
	eigen
	# insert subdirectories here, one per line
	)

foreach(subdir ${subdirectories} )
	if((NOT ${subdir} STREQUAL "vtk" OR ${ENABLE_VTK}) AND (NOT ${subdir} STREQUAL "metis"  OR ${USE_METIS}))
		add_subdirectory(${subdir} ${CMAKE_CURRENT_BINARY_DIR}/${subdir})
		set( libs ${libs} ${gedim_external_${subdir}_lib} )
		set( headers ${headers} ${gedim_external_${subdir}_headers} )
		set( includes ${includes} ${gedim_external_${subdir}_include} )
		set( configure ${configure} ${gedim_external_${subdir}_configure} )
	endif()
endforeach()

if(NOT "${configure}" STREQUAL "")
	message(WARNING "Run of 'make configure' required")
	add_custom_target(configure
		COMMAND ${CMAKE_MAKE_PROGRAM} ${configure} && cmake ${CMAKE_CURRENT_SOURCE_DIR})
else()

	# WORKAROUND FOR AVOIDING BUG IN METIS MAKEFILE
	if(${USE_METIS})
		foreach(metis_fake_dep ${libs})
			if(NOT ${metis_fake_dep} MATCHES "metis")
				add_dependencies(metis ${metis_fake_dep})
			endif()
		endforeach()
	endif()

endif()
