cmake_minimum_required(VERSION 3.0)

set( subdirectories
	IO
	common
	geometry
	mpiTools
	# insert subdirectories here, one per line
	)

foreach( subdir ${subdirectories} )
	add_subdirectory(${subdir})
	set( sources ${sources} ${gedim_core_${subdir}_source} )
	set( headers ${headers} ${gedim_core_${subdir}_headers} )
endforeach()

set( gedim_core_source ${sources} PARENT_SCOPE )
set( gedim_core_headers ${headers} PARENT_SCOPE )
