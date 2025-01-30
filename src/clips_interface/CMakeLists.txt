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

target_include_directories(ffi_clips_interface PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface>)

target_include_directories(ffi_clips_interface
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_compile_options(-fPIC)

add_subdirectory(n3parser)
add_subdirectory(numeric)
add_subdirectory(lists)
add_subdirectory(objects)
add_subdirectory(crifi_time)
add_subdirectory(external_functions)
add_subdirectory(tools)

target_link_libraries(ffi_clips_interface PUBLIC
	clips
)

target_link_libraries(ffi_clips_interface PRIVATE
	external_functions
	n3parser
	crifi_time
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
