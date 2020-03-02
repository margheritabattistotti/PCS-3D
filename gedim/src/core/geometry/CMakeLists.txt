cmake_minimum_required(VERSION 3.0)

set(gedim_core_geometry_source
	${CMAKE_CURRENT_SOURCE_DIR}/IRotation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Polygon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Segment.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Measurer.cpp
	PARENT_SCOPE)

set(gedim_core_geometry_headers
	${CMAKE_CURRENT_SOURCE_DIR}/GeometricObject.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/IRotation.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Polyhedron.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Polygon.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Segment.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Vertex.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/IGeometricObject.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ISegment.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/IPolygon.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/IPolyhedron.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Measurer.hpp
	PARENT_SCOPE)
