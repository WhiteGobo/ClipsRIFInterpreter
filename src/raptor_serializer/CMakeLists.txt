add_library(raptor_serializer
	raptor_serializer.c
	raptor_serializer.h
)

set_target_properties(raptor_serializer PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/raptor_serializer.h
	OUTPUT_NAME "raptor_serializer"
)

target_include_directories(raptor_serializer PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

target_link_libraries(raptor_serializer PUBLIC
	ffi_clips_interface
	raptor
)

include(include_raptor.cmake)
