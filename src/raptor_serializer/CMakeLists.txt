add_library(crifi_raptor
	crifi_raptor.h
	raptor_serializer.c
	raptor_serializer.h
	clips_script_serializer.c
	clips_script_serializer.h
	crifi_raptor_interface.c
	crifi_raptor_interface.h
	parse_with_raptor.c
	rdf_object.c
	rdf_object.h
)

set_target_properties(crifi_raptor PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/crifi_raptor.h
	OUTPUT_NAME "crifi_raptor"
)

target_include_directories(crifi_raptor PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

include(include_raptor.cmake)

target_link_libraries(crifi_raptor PUBLIC
	ffi_clips_interface
	raptor2
)

target_link_libraries(crifi_raptor PRIVATE
	info_query
	n3parser
	crifi_lists
)

