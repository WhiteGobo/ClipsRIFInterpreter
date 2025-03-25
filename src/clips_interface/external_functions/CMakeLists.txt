add_library(external_functions STATIC
	external_functions.c
	math_user_defined_functions.c
	pred_user_defined_functions.c
	list_user_defined_functions.c
	binary_user_defined_functions.c
	boolean_user_defined_functions.c
	time_user_defined_functions.c
	xmlliteral_user_defined_functions.c
	string_user_defined_functions.c
	plainliteral_user_defined_functions.c
	own_user_defined_functions.c
	external_functions.h
	clipsvalue_check_datatype.c
	import_user_defined_functions.h
	import_user_defined_functions.c
)

#add_compile_options(-fPIC)

target_include_directories(external_functions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(external_functions PRIVATE ${CRIFI_SHARED_HEADER})

#set_target_properties(external_functions PROPERTIES
#	PUBLIC_HEADER external_functions.h
#	OUTPUT_NAME "external_functions"
#)

target_link_libraries(external_functions PRIVATE
	#n3parser
	info_query
	clips
	crifi_lists
	crifi_objects
	crifi_time
	crifi_numeric
	crifi_tools
	crifi_import
)
