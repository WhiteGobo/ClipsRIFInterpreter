project(ffi_clips_interface VERSION 0.1.0 LANGUAGES C)

add_library(ffi_clips_interface
	ffi_clips_interface.c
	graph_engine.c
	clips_to_interface.c
)

set_target_properties(ffi_clips_interface PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/interface/ffi_clips_interface.h
	OUTPUT_NAME "ffi_clips_interface"
)

#Directory containing headerfiles shared between crifi libraries.
#Used for shared URIs and methods.
set(CRIFI_SHARED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/interface/")

target_include_directories(ffi_clips_interface PUBLIC
	$<BUILD_INTERFACE:${CRIFI_SHARED_HEADER}>)

target_include_directories(ffi_clips_interface
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(interface)
add_subdirectory(n3parser)
add_subdirectory(numeric)
add_subdirectory(lists)
add_subdirectory(objects)
add_subdirectory(crifi_time)
add_subdirectory(external_functions)
add_subdirectory(tools)
add_subdirectory(info_query)
add_subdirectory(importdirective)

target_link_libraries(ffi_clips_interface PUBLIC
	clips
)

target_link_libraries(ffi_clips_interface PRIVATE
	crifi_public_interface
	external_functions
	n3parser
	crifi_time
	info_query
	crifi_import
)

#if(TARGET SqrtLibrary)
set(installable_libs ${installable_libs} ffi_clips_interface PARENT_SCOPE)
#endif()

#install(TARGETS ffi_clips_interface
#	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#if(BUILD_SHARED_LIBS)
#	install(TARGETS ffi_clips_interface
#		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#	)
#endif()
