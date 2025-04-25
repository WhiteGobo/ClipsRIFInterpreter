add_library(info_query STATIC
	info_query.h
	info_query.c
	blanknodes.c
	genclipscode.c
	internal_fact_interface.c
)

set_target_properties(info_query PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/info_query.h
	OUTPUT_NAME "info_query"
)

target_include_directories(info_query
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(info_query PUBLIC
	#ffi_clips_interface
	crifi_public_interface
	n3parser #for extract_literal -_datatype and -_lang
)

target_link_libraries(info_query PRIVATE
	crifi_lists
)
