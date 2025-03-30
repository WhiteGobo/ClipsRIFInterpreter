include(import_as_source.cmake)

add_library(crifi_import_implementations
	crifi_import_implementations.c
	crifi_import_implementations.h
	import_from_file.c
	import_from_file.h
)

target_include_directories(crifi_import_implementations PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(crifi_import_implementations PUBLIC
	crifi_raptor
	ffi_clips_interface
)

target_link_libraries(crifi_import_implementations PRIVATE
	crifi_import
	info_query
)
