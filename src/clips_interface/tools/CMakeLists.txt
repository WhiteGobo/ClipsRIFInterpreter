add_library(crifi_tools STATIC
	uriencode.c
	uriencode.h
	xpath_replace.c
	xpath_replace.h
	check_datatype.c
	check_datatype.h
)

set_target_properties(crifi_tools PROPERTIES
	PUBLIC_HEADER tools.h
	OUTPUT_NAME "crifi_tools"
)

target_include_directories(crifi_tools
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")

target_include_directories(crifi_tools
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../interface/")
