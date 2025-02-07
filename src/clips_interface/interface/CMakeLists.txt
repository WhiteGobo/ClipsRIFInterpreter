add_library(crifi_public_interface STATIC
	interface.c
	ffi_clips_interface.h
)

set_target_properties(crifi_public_interface PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/ffi_clips_interface.h
)

target_include_directories(crifi_public_interface PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

target_link_libraries(crifi_public_interface PUBLIC
	clips
)
