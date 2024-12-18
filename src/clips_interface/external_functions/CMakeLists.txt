add_library(external_functions SHARED
	external_functions.c
	math_user_defined_functions.c
	pred_user_defined_functions.c
	list_user_defined_functions.c
	binary_user_defined_functions.c
	own_user_defined_functions.c
	external_functions.h
)

target_include_directories(external_functions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(external_functions PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../interface/")

set_target_properties(external_functions PROPERTIES
  PUBLIC_HEADER external_functions.h
  OUTPUT_NAME "external_functions"
)

target_link_libraries(
	external_functions
	n3parser
	clips
	crifi_lists
	crifi_objects
)
