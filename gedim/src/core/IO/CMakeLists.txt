cmake_minimum_required(VERSION 3.0)

set(gedim_core_IO_source
	${CMAKE_CURRENT_SOURCE_DIR}/Output.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ConfigFile.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EigenExtension.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EncodeBase64.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/UnitTestResult.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/UnitTestSummary.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StringUtilities.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/CsvExporter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IniExporter.cpp
	PARENT_SCOPE)

set(gedim_core_IO_headers
	${CMAKE_CURRENT_SOURCE_DIR}/Output.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ConfigFile.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/EigenExtension.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/EncodeBase64.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/UnitTestResult.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/UnitTestSummary.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Input.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/InputProperty.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/StringUtilities.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/CsvExporter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/IniExporter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ICsvExport.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/IIniExport.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/InputPropertySupportedTypes.hpp
	PARENT_SCOPE)
