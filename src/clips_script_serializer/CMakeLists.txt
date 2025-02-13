add_library(clips_script_serializer
	clips_script_serializer.c
	clips_script_serializer.h
)

set_target_properties(clips_script_serializer PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/clips_script_serializer.h
	OUTPUT_NAME "clips_script_serializer"
)

target_include_directories(clips_script_serializer PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

target_link_libraries(clips_script_serializer PUBLIC
	ffi_clips_interface
)

#target_link_libraries(clips_script_serializer PRIVATE
#	info_query
#)
