set(gedim_core_common_source
	# insert source files here, one per line
	PARENT_SCOPE
	)
set(gedim_core_common_headers
	# insert header files here, one per line
	${CMAKE_CURRENT_SOURCE_DIR}/MacroDefinitions.hpp.in
	${CMAKE_CURRENT_SOURCE_DIR}/DefineNumbers.hpp
	PARENT_SCOPE
	)
