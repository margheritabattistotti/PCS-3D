add_custom_target(eigenExtract ALL cp -r ${CMAKE_CURRENT_SOURCE_DIR}/eigen/include ${CMAKE_CURRENT_BINARY_DIR})
set(gedim_external_eigen_lib eigenExtract PARENT_SCOPE)
